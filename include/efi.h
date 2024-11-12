#pragma once
#include <stdarg.h>
#include <efi_boot_service_table.h>
#include <efi_runtime_services.h>
#include <efi_system_table.h>
#include <efi_types.h>


#define isdigit_c16(c)  ((c) >= u'0' && (c) <= u'9')

// ================================
// Print a number to stdout
// ================================
BOOLEAN print_number(UINTN number, UINT8 base, BOOLEAN is_signed, UINTN min_digits, CHAR16 *buf, 
                     UINTN *buf_idx, EFI_SYSTEM_TABLE *systable) {
    
    const CHAR16 *digits = u"0123456789ABCDEF";
    CHAR16 buffer[24];  
    UINTN i = 0;
    BOOLEAN negative = false;

    if (base > 16) {
        systable->ConOut->OutputString(systable->ConOut, u"Invalid base specified!\r\n");
        return false;  
    }

    // Handle signed numbers for decimal
    if (base == 10 && is_signed && (size_t)number < 0) {
       number = (size_t)-number;  
       negative = true;
    }

    // Convert number to string
    do {
       buffer[i++] = digits[number % base];
       number /= base;
    } while (number > 0);

    // Pad with zeros
    while (i < min_digits) buffer[i++] = u'0'; 

    // Add negative sign if needed
    if (base == 10 && negative) buffer[i++] = u'-';

    buffer[i--] = u'\0';

    // Reverse buffer for correct number order
    for (UINTN j = 0; j < i; j++, i--) {
        UINTN temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    // Append to main buffer for printing
    for (CHAR16 *p = buffer; *p; p++) {
        buf[*buf_idx] = *p;
        *buf_idx += 1;
    }
    return true;
}

// ===================================================================
// Print formatted strings to stdout, using a va_list for arguments
// ===================================================================
bool uwuvfprintf(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *stream, CHAR16 *fmt, va_list args, EFI_SYSTEM_TABLE *systable) {
    bool result = true;
    CHAR16 charstr[2] = {0};    
    CHAR16 buf[1024];   
    UINTN buf_idx = 0;

    for (UINTN i = 0; fmt[i] != u'\0'; i++) {
        if (fmt[i] == u'%') {
            bool alternate_form = false;
            UINTN min_field_width = 0;
            UINTN precision = 0;
            UINTN length_bits = 0;  
            UINT8 base = 0;
            bool signed_num = false;
            bool numeric = false;
            bool left_justify = false;  
            CHAR16 padding_char = u' ';  

            i++; // Skip '%'

            // Parse flags
            while (true) {
                switch (fmt[i]) {
                    case u'#': alternate_form = true; i++; break;
                    case u'0': padding_char = u'0'; i++; break;
                    case u'-': left_justify = true; i++; break;
                    default: break;
                }
                if (fmt[i] != u'#' && fmt[i] != u'0' && fmt[i] != u'-') {
                    break;  // No more flags, break the loop
                }
            }

            // Get minimum field width
            if (fmt[i] == u'*') {
                min_field_width = va_arg(args, int);
                i++;
            } else {
                while (isdigit_c16(fmt[i])) {
                    min_field_width = (min_field_width * 10) + (fmt[i++] - u'0');
                }
            }

            // Handle precision
            if (fmt[i] == u'.') {
                i++;
                if (fmt[i] == u'*') {
                    precision = va_arg(args, int);
                    i++;
                } else {
                    while (isdigit_c16(fmt[i])) {
                        precision = (precision * 10) + (fmt[i++] - u'0');
                    }
                }
            }

            // Handle length modifiers (h, l)
            if (fmt[i] == u'h') {
                i++;
                length_bits = (fmt[i] == u'h') ? 8 : 16;
                i += (fmt[i] == u'h') ? 1 : 0;
            } else if (fmt[i] == u'l') {
                i++;
                length_bits = (fmt[i] == u'l') ? 64 : 32;
                i += (fmt[i] == u'l') ? 1 : 0;
            }

            // Handle specifier types
            switch (fmt[i]) {
                case u'c': {
                    charstr[0] = (length_bits == 8) ? (CHAR16)(va_arg(args, int)) : (CHAR16)(va_arg(args, int));
                    buf[buf_idx++] = charstr[0];
                } break;

                case u's': {
                    CHAR16 *string = va_arg(args, CHAR16*);
                    while (*string) {
                        buf[buf_idx++] = *string++;
                        if (++precision == 0) break;  // Stop if precision is 0
                    }
                } break;

                case u'd': case u'u': case u'x': case u'b': case u'o': {
                    numeric = true;
                    switch (fmt[i]) {
                        case u'd': base = 10; signed_num = true; break;
                        case u'u': base = 10; signed_num = false; break;
                        case u'x': base = 16; signed_num = false; break;
                        case u'b': base = 2; signed_num = false; break;
                        case u'o': base = 8; signed_num = false; break;
                    }

                    if (alternate_form) {
                        buf[buf_idx++] = (fmt[i] == u'x') ? u'0' : u'0';
                        buf[buf_idx++] = (fmt[i] == u'x') ? u'x' : u'o';
                    }

                    UINT64 number = va_arg(args, UINT32);
                    print_number(number, base, signed_num, precision, buf, &buf_idx, systable);
                } break;

                default:
                    stream->OutputString(stream, u"Invalid format specifier: %");
                    charstr[0] = fmt[i];
                    stream->OutputString(stream, charstr);
                    stream->OutputString(stream, u"\r\n");
                    result = false;
                    break;  // Exit the switch-case block
            }

            // Print result with padding if necessary
            buf[buf_idx] = u'\0';  // Null-terminate the string
            if (padding_char == u'0' && (left_justify || precision > 0)) {
                padding_char = u' ';  // Override to space if justification or precision applies
            }

            charstr[0] = padding_char;
            charstr[1] = u'\0';

            if (left_justify) {
                stream->OutputString(stream, buf);
                while (buf_idx < min_field_width) {
                    stream->OutputString(stream, charstr);
                    buf_idx++;
                }
            } else {
                while (buf_idx < min_field_width) {
                    stream->OutputString(stream, charstr);
                    buf_idx++;
                }
                stream->OutputString(stream, buf);
            }

        } else {
            charstr[0] = fmt[i];
            stream->OutputString(stream, charstr);
        }
    }

    va_end(args);
    return result;
}

bool uwuprintf(EFI_SYSTEM_TABLE* systable ,CHAR16 *fmt, ...) {
    bool result = true;
    va_list args;
    va_start(args, fmt);
    result = uwuvfprintf(systable->ConOut, fmt, args, systable);
    va_end(args);
    return result;
}
