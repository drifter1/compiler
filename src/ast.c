#include "../include/compiler.h"

/* ---------------------AST STRUCTURE----------------------- */

ast_node *ast;

/* ------------------AST NODE MANAGEMENT-------------------- */

ast_node *new_ast_node(ast_node_kind kind) {
    ast_node *node = (ast_node *)malloc(sizeof(ast_node));

    node->kind = kind;

#if DEBUG
    printf("Created new AST node of kind \'%s\'\n",
           ast_node_kind_to_string(kind));
#endif

    return node;
}

ast_node *ast_program(list_node *declarations, list_node *functions,
                      ast_node *main_function) {
    ast_node *v = new_ast_node(PROGRAM);

    v->as.program.declarations = declarations;
    v->as.program.functions = functions;
    v->as.program.main_function = main_function;

    v->lineno = ast_program_lineno(v);

    return v;
}

ast_node *ast_declaration(data_type d_type, list_node *names) {
    ast_node *v = new_ast_node(DECLARATION);

    v->lineno = yylineno;

    v->as.declaration.d_type = d_type;
    v->as.declaration.names = names;

    return v;
}

ast_node *ast_constant(data_type d_type, value val) {
    ast_node *v = new_ast_node(CONSTANT);

    v->lineno = yylineno;

    v->as.constant.d_type = d_type;
    v->as.constant.val = val;

    return v;
}

ast_node *ast_function(symtab_entry *entry, ast_node *function_tail) {
    ast_node *v = new_ast_node(FUNCTION);

    v->lineno = function_tail->lineno - 1;

    v->as.function.entry = entry;
    v->as.function.function_tail = function_tail;

    return v;
}

ast_node *ast_function_tail(list_node *declarations, list_node *statements) {
    ast_node *v = new_ast_node(FUNCTION_TAIL);

    v->as.function_tail.declarations = declarations;
    v->as.function_tail.statements = statements;

    v->lineno = ast_function_tail_lineno(v);

    return v;
}

ast_node *ast_if_statement(ast_node *condition, list_node *if_branch,
                           list_node *else_if_branches,
                           list_node *else_branch) {
    ast_node *v = new_ast_node(IF_STATEMENT);

    v->lineno = condition->lineno;

    v->as.if_statement.condition = condition;
    v->as.if_statement.if_branch = if_branch;
    v->as.if_statement.else_if_branches = else_if_branches;
    v->as.if_statement.else_branch = else_branch;

    return v;
}

ast_node *ast_expression_binary(ast_node *left, operator_type op_type,
                                ast_node *right) {
    ast_node *v = new_ast_node(EXPRESSION_BINARY);

    v->lineno = yylineno;

    v->as.expression_binary.left = left;
    v->as.expression_binary.op_type = op_type;
    v->as.expression_binary.right = right;
    v->as.expression_binary.d_type = UNDEF_TYPE;

    return v;
}

ast_node *ast_expression_unary(ast_node *operand, operator_type op_type,
                               fixity_type fixity) {
    ast_node *v = new_ast_node(EXPRESSION_UNARY);

    v->lineno = yylineno;

    v->as.expression_unary.operand = operand;
    v->as.expression_unary.op_type =
        ast_expression_unary_op_type(op_type, fixity);
    v->as.expression_unary.d_type = UNDEF_TYPE;

    return v;
}

ast_node *ast_variable_reference(symtab_entry *entry) {
    ast_node *v = new_ast_node(VARIABLE_REFERENCE);

    v->lineno = yylineno;

    v->as.variable_reference.entry = entry;

    return v;
}

ast_node *ast_function_call(symtab_entry *entry, list_node *arguments) {
    ast_node *v = new_ast_node(FUNCTION_CALL);

    v->lineno = yylineno;

    v->as.function_call.entry = entry;
    v->as.function_call.arguments = arguments;

    return v;
}

ast_node *ast_else_if(ast_node *condition, list_node *else_if_branch) {
    ast_node *v = new_ast_node(ELSE_IF);

    v->lineno = condition->lineno;

    v->as.else_if.condition = condition;
    v->as.else_if.else_if_branch = else_if_branch;

    return v;
}

ast_node *ast_for_loop(ast_node *initialize, ast_node *condition,
                       ast_node *increment, list_node *for_branch) {
    ast_node *v = new_ast_node(FOR_LOOP);

    v->lineno = initialize->lineno;

    v->as.for_loop.initialize = initialize;
    v->as.for_loop.condition = condition;
    v->as.for_loop.increment = increment;
    v->as.for_loop.for_branch = for_branch;

    return v;
}

ast_node *ast_assignment(ast_node *variable_reference, ast_node *expression) {
    ast_node *v = new_ast_node(ASSIGNMENT);

    v->lineno = yylineno;

    v->as.assignment.variable_reference = variable_reference;
    v->as.assignment.expression = expression;

    return v;
}

ast_node *ast_while_loop(ast_node *condition, list_node *while_branch) {
    ast_node *v = new_ast_node(WHILE_LOOP);

    v->lineno = condition->lineno;

    v->as.while_loop.condition = condition;
    v->as.while_loop.while_branch = while_branch;

    return v;
}

ast_node *ast_jump_statement(jump_type j_type) {
    ast_node *v = new_ast_node(JUMP_STATEMENT);

    v->lineno = yylineno;

    v->as.jump_statement.j_type = j_type;

    return v;
}

ast_node *ast_print_statement(print_type p_type, const char *sval,
                              ast_node *expression) {
    ast_node *v = new_ast_node(PRINT_STATEMENT);

    v->lineno = yylineno;

    v->as.print_statement.p_type = p_type;

    switch (p_type) {
    case EXPRESSION:
        v->as.print_statement.print_value.expression = expression;
        break;
    case STRING:
        v->as.print_statement.print_value.sval = sval;
    }

    return v;
}

ast_node *ast_input_statement(ast_node *variable_reference) {
    ast_node *v = new_ast_node(INPUT_STATEMENT);

    v->lineno = yylineno;

    v->as.input_statement.variable_reference = variable_reference;

    return v;
}

ast_node *ast_return_statement(data_type ret_type, ast_node *expression) {
    ast_node *v = new_ast_node(RETURN_STATEMENT);

    v->lineno = yylineno;

    v->as.return_statement.ret_type = ret_type;
    v->as.return_statement.expression = expression;

    return v;
}

void free_ast_node(ast_node *node) {
    if (node == NULL)
        return;

    switch (node->kind) {
    case PROGRAM:
        free_ast_node_list(node->as.program.declarations);
        free_ast_node_list(node->as.program.functions);
        free_ast_node(node->as.program.main_function);
        break;
    case DECLARATION:
        list_free(node->as.declaration.names);
        break;
    case CONSTANT:
        break;
    case FUNCTION:
        /* entry handled in symtab */
        free_ast_node(node->as.function.function_tail);
        break;
    case FUNCTION_TAIL:
        free_ast_node_list(node->as.function_tail.declarations);
        free_ast_node_list(node->as.function_tail.statements);
        break;
    case IF_STATEMENT:
        free_ast_node(node->as.if_statement.condition);
        free_ast_node_list(node->as.if_statement.if_branch);
        free_ast_node_list(node->as.if_statement.else_branch);
        free_ast_node_list(node->as.if_statement.else_if_branches);
        break;
    case EXPRESSION_BINARY:
        free_ast_node(node->as.expression_binary.left);
        free_ast_node(node->as.expression_binary.right);
        break;
    case EXPRESSION_UNARY:
        free_ast_node(node->as.expression_unary.operand);
        break;
    case VARIABLE_REFERENCE:
        /* entry handled in symtab */
        break;
    case FUNCTION_CALL:
        /* entry handled in symtab */
        free_ast_node_list(node->as.function_call.arguments);
        break;
    case ELSE_IF:
        free_ast_node_list(node->as.else_if.else_if_branch);
        break;
    case FOR_LOOP:
        free_ast_node(node->as.for_loop.initialize);
        free_ast_node(node->as.for_loop.condition);
        free_ast_node(node->as.for_loop.increment);
        free_ast_node_list(node->as.for_loop.for_branch);
        break;
    case ASSIGNMENT:
        free_ast_node((node->as.assignment.variable_reference));
        free_ast_node((node->as.assignment.expression));
        break;
    case WHILE_LOOP:
        free_ast_node(node->as.while_loop.condition);
        free_ast_node_list(node->as.while_loop.while_branch);
        break;
    case JUMP_STATEMENT:
        break;
    case PRINT_STATEMENT:
        switch (node->as.print_statement.p_type) {
        case EXPRESSION:
            free_ast_node(node->as.print_statement.print_value.expression);
            break;
        case STRING:
            break;
        }
        break;
    case INPUT_STATEMENT:
        free_ast_node(node->as.input_statement.variable_reference);
        break;
    case RETURN_STATEMENT:
        free_ast_node(node->as.return_statement.expression);
        break;
    }

    free(node);
    node = NULL;
}

void free_ast_node_list(list_node *list_head) {
    list_node *head;
    ast_node *node;
    head = list_head;
    while (head != NULL) {
        node = (ast_node *)head->data;
        free_ast_node(node);
        head = head->next;
    }
}

/* --------------------AST NODE HELPERS--------------------- */

int ast_program_lineno(ast_node *node) {
    if (node->as.program.declarations != NULL) {
        ast_node *declaration = (ast_node *)node->as.program.declarations->data;
        return declaration->lineno;
    }

    if (node->as.program.functions != NULL) {
        ast_node *function = (ast_node *)node->as.program.functions->data;
        return function->lineno;
    }

    return node->as.program.main_function->lineno;
}

int ast_function_tail_lineno(ast_node *node) {
    if (node->as.function_tail.declarations != NULL) {
        ast_node *declaration =
            (ast_node *)node->as.function_tail.declarations->data;
        return declaration->lineno;
    }

    ast_node *statement = (ast_node *)node->as.function_tail.statements->data;
    return statement->lineno;
}

ast_node *ast_constant_undef() {
    value val;
    val.ival = 0;
    return ast_constant(UNDEF_TYPE, val);
}

ast_node *ast_constant_init(symtab_entry *entry) {
    data_type d_type = entry->as.variable.init_value.d_type;
    value val = entry->as.variable.init_value.val;
    return ast_constant(d_type, val);
}

ast_node *ast_constant_zero(data_type d_type) {
    value val;
    switch (d_type) {
    case UNDEF_TYPE:
        val.ival = 0;
        break;
    case INT_TYPE:
        val.ival = 0;
        break;
    case CHAR_TYPE:
        val.cval = 0;
        break;
    case FLOAT_TYPE:
    case DOUBLE_TYPE:
        val.fval = 0.0;
        break;
    case VOID_TYPE:
        val.ival = 0;
        break;
    }
    return ast_constant(d_type, val);
}

operator_type ast_expression_unary_op_type(operator_type op_type,
                                           fixity_type fixity) {
    switch (op_type) {
    case INC:
        switch (fixity) {
        case PREFIX:
            return PRE_INC;
            break;
        case POSTFIX:
            return POST_INC;
        }
        break;
    case DEC:
        switch (fixity) {
        case PREFIX:
            return PRE_DEC;
            break;
        case POSTFIX:
            return POST_DEC;
        }
        break;
    case ADD:
        return UNARY_PLUS;
        break;
    case SUB:
        return UNARY_MINUS;
        break;
    default:
        return op_type;
    }

    return op_type;
}

char *ast_node_kind_to_string(ast_node_kind kind) {
    switch (kind) {
    case PROGRAM:
        return "program";
    case DECLARATION:
        return "declaration";
    case CONSTANT:
        return "constant";
    case FUNCTION:
        return "function";
    case FUNCTION_TAIL:
        return "function_tail";
    case IF_STATEMENT:
        return "if_statement";
    case EXPRESSION_BINARY:
        return "expression_binary";
    case EXPRESSION_UNARY:
        return "expression_unary";
    case VARIABLE_REFERENCE:
        return "variable_reference";
    case FUNCTION_CALL:
        return "function_call";
    case ELSE_IF:
        return "else_if";
    case FOR_LOOP:
        return "for_loop";
    case ASSIGNMENT:
        return "assignment";
    case WHILE_LOOP:
        return "while_loop";
    case JUMP_STATEMENT:
        return "jump_statement";
    case PRINT_STATEMENT:
        return "print_statement";
    case INPUT_STATEMENT:
        return "input_statement";
    case RETURN_STATEMENT:
        return "return_statement";
    }
    return "_error";
}