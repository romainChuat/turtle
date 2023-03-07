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

/* 
 *  CMD_SIMPLE 
 */

struct ast_node *make_cmd_up(void) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_down(void) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HEADING;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_position(struct ast_node *valueX, struct ast_node *valueY) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 2;
  node->children[0] = valueX;
  node->children[1] = valueY;
  return node;
}

struct ast_node *make_cmd_home(void) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HOME;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_colorRGB(struct ast_node *R,struct ast_node *G, struct ast_node *B){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 3;
  node->children[0] = R;
  node->children[1] = G;
  node->children[2] = B;
  return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_PRINT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

/* 
 * 
 */




void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {
  self->x = 0;
  self->y = 0;
  self->angle = 0;
  self->up = false;
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {
  
}

/*
 * print
 */

void print_expr(const struct ast_node *expr) {
  switch (expr->kind) {
    case KIND_EXPR_VALUE:
      printf("%g", expr->u.value);
      break;
    default:
      assert("invalid expression kind");
      break;
  }
}

void print_cmd(const struct ast_node *cmd) {
  switch (cmd->u.cmd) {
    case CMD_UP:
      printf("UP");
      break;
    case CMD_DOWN:
      printf("DOWN");
      break;
    case CMD_RIGHT:
      printf("RIGHT ");
      print_expr(cmd->children[0]);
      break;
    case CMD_LEFT:
      printf("LEFT ");
      print_expr(cmd->children[0]);
      break;
    case CMD_HEADING:
      printf("HEADING ");
      print_expr(cmd->children[0]);
      break;
    case CMD_FORWARD:
      printf("FORWARD ");
      print_expr(cmd->children[0]);
      break;
    case CMD_BACKWARD:
      printf("BACKWARD ");
      print_expr(cmd->children[0]);
      break;
    case CMD_POSITION:
      printf("POSITION ");
      print_expr(cmd->children[0]);
      printf(" ");
      print_expr(cmd->children[1]);
      break;
    case CMD_HOME:
      printf("HOME");
      break;
    case CMD_COLOR:
      printf("COLOR ");
      print_expr(cmd->children[0]);
      if (cmd->children_count == 3) {
        printf(" ");
        print_expr(cmd->children[1]);
        printf(" ");
        print_expr(cmd->children[2]);
      }
      break;
    case CMD_PRINT:
      printf("PRINT ");
      print_expr(cmd->children[0]);
      break;
    default:
      assert("invalid command kind");
      break;
  }
}

void ast_print(const struct ast *self) {
  for (size_t i = 0; i < self->unit->children_count; ++i) {
    const struct ast_node *node = self->unit->children[i];
    //for(size_t j = 0; j < node->children_count; j++) {

      switch (node->kind) {
        case KIND_EXPR_VALUE:
          printf("Value ");
          print_expr(node);
          break;
        case KIND_CMD_SIMPLE:
          printf("Command ");
          print_cmd(node);
          break;
        default:
          assert("invalid node kind");
          break;
      }
      printf("\n");
    //}
  }
}


