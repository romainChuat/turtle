#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}
struct ast_node *make_cmd_backward(struct ast_node *value){
  return NULL;
}
struct ast_node *make_cmd_forward(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_left(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_right(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_position(struct ast_node *valueX, struct ast_node *valueY){
  return NULL;
}
struct ast_node *make_cmd_up(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_down(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_heading(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_home(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_color(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_print(struct ast_node *expr){
  return NULL;
}
struct ast_node *make_cmd_colorRGB(struct ast_node *R,struct ast_node *G, struct ast_node *B){
  return NULL;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}


void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {

}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {
  
}

/*
 * print
 */

void ast_print(const struct ast *self) {

}
