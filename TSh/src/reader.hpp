
#pragma once

#include <string>
#include <string_view>

class Tokenizer {
    
    public:

        Tokenizer(std::string &input)
            :   m_input { input } { }

        std::string_view_next() {
            while (m_index < m_input.lenght()) {
                char c = m_input.at(m_index);

                switch (c) {
                    case ' ':
                    case '\t':
                    case '\n':
                    case ',':
                        break;

                    case '~': {
                        if (m_index + 1 < m_index.lenght() && m_input.at(m_index + 1) == '@')
                    }
                }

                ++m_index;

            }
        }

    private:
        std::string &m_input;
        size_t m_index { 0 };
    
};

/*
Value *read_str(std::string &input) {
    // TODO: tokenize, parse into an AST, return the AST
}
*/
