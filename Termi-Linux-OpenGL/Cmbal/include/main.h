#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "visitor.h"
#include "io.h"
#include "helper.h"

int cmbal_execute(const char* path)
{
    lexer_T* lexer = init_lexer(get_file_contents(path));
    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser, parser->scope);
    visitor_T* visitor = init_visitor();
    visitor_visit(visitor, root);
}
#endif