/* A recursive-descent parser generated by greg 0.4.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct _GREG;
#define YYRULECOUNT 1

// This is the grammar file for decadence
// @author Amos Wenger

// Now every hook has a 'this' pointer
void gotLust(void *this);

// Store the state of the parser
struct _ParserState {
    /* A pointer to the instance of our Parser */
    void *this;
};

typedef struct _ParserState ParserState;

#define YY_XTYPE ParserState *
#define YY_XVAR core


#ifndef YY_ALLOC
#define YY_ALLOC(N, D) malloc(N)
#endif
#ifndef YY_CALLOC
#define YY_CALLOC(N, S, D) calloc(N, S)
#endif
#ifndef YY_REALLOC
#define YY_REALLOC(B, N, D) realloc(B, N)
#endif
#ifndef YY_FREE
#define YY_FREE free
#endif
#ifndef YY_LOCAL
#define YY_LOCAL(T)     static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)    static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)      static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)     T
#endif
#ifndef YY_NAME
#define YY_NAME(N) yy##N
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)                 \
  {                                                     \
    int yyc= getchar();                                 \
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);        \
    yyprintf((stderr, "<%c>", yyc));                  \
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN        ( G->begin= G->pos, 1)
#endif
#ifndef YY_END
#define YY_END          ( G->end= G->pos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args) fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YY_XTYPE
#define YY_XTYPE void *
#endif
#ifndef YY_XVAR
#define YY_XVAR yyxvar
#endif

#ifndef YY_STACK_SIZE
#define YY_STACK_SIZE 128
#endif

#ifndef YY_PART
#define yydata G->data
#define yy G->ss

struct _yythunk; // forward declaration
typedef void (*yyaction)(struct _GREG *G, char *yytext, int yyleng, struct _yythunk *thunkpos, YY_XTYPE YY_XVAR);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

typedef struct _GREG {
  char *buf;
  int buflen;
  int   offset;
  int   pos;
  int   limit;
  char *text;
  int   textlen;
  int   begin;
  int   end;
  yythunk *thunks;
  int   thunkslen;
  int thunkpos;
  YYSTYPE ss;
  YYSTYPE *val;
  YYSTYPE *vals;
  int valslen;
  YY_XTYPE data;
} GREG;

YY_LOCAL(int) yyrefill(GREG *G)
{
  int yyn;
  YY_XTYPE YY_XVAR = (YY_XTYPE) G->data;
  while (G->buflen - G->pos < 512)
    {
      G->buflen *= 2;
      G->buf= YY_REALLOC(G->buf, G->buflen, G->data);
    }
  YY_INPUT((G->buf + G->pos), yyn, (G->buflen - G->pos));
  if (!yyn) return 0;
  G->limit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(GREG *G)
{
  if (G->pos >= G->limit && !yyrefill(G)) return 0;
  ++G->pos;
  return 1;
}

YY_LOCAL(int) yymatchChar(GREG *G, int c)
{
  if (G->pos >= G->limit && !yyrefill(G)) return 0;
  if ((unsigned char)G->buf[G->pos] == c)
    {
      ++G->pos;
      yyprintf((stderr, "  ok   yymatchChar(%c) @ %s\n", c, G->buf+G->pos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(%c) @ %s\n", c, G->buf+G->pos));
  return 0;
}

YY_LOCAL(int) yymatchString(GREG *G, char *s)
{
  int yysav= G->pos;
  while (*s)
    {
      if (G->pos >= G->limit && !yyrefill(G)) return 0;
      if (G->buf[G->pos] != *s)
        {
          G->pos= yysav;
          return 0;
        }
      ++s;
      ++G->pos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(GREG *G, unsigned char *bits)
{
  int c;
  if (G->pos >= G->limit && !yyrefill(G)) return 0;
  c= (unsigned char)G->buf[G->pos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++G->pos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", G->buf+G->pos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", G->buf+G->pos));
  return 0;
}

YY_LOCAL(void) yyDo(GREG *G, yyaction action, int begin, int end)
{
  while (G->thunkpos >= G->thunkslen)
    {
      G->thunkslen *= 2;
      G->thunks= YY_REALLOC(G->thunks, sizeof(yythunk) * G->thunkslen, G->data);
    }
  G->thunks[G->thunkpos].begin=  begin;
  G->thunks[G->thunkpos].end=    end;
  G->thunks[G->thunkpos].action= action;
  ++G->thunkpos;
}

YY_LOCAL(int) yyText(GREG *G, int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (G->textlen < (yyleng - 1))
        {
          G->textlen *= 2;
          G->text= YY_REALLOC(G->text, G->textlen, G->data);
        }
      memcpy(G->text, G->buf + begin, yyleng);
    }
  G->text[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(GREG *G)
{
  int pos;
  for (pos= 0; pos < G->thunkpos; ++pos)
    {
      yythunk *thunk= &G->thunks[pos];
      int yyleng= thunk->end ? yyText(G, thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, G->text));
      thunk->action(G, G->text, yyleng, thunk, G->data);
    }
  G->thunkpos= 0;
}

YY_LOCAL(void) yyCommit(GREG *G)
{
  if ((G->limit -= G->pos))
    {
      memmove(G->buf, G->buf + G->pos, G->limit);
    }
  G->offset += G->pos;
  G->begin -= G->pos;
  G->end -= G->pos;
  G->pos= G->thunkpos= 0;
}

YY_LOCAL(int) yyAccept(GREG *G, int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone(G);
      yyCommit(G);
    }
  return 1;
}

YY_LOCAL(void) yyPush(GREG *G, char *text, int count, yythunk *thunk, YY_XTYPE YY_XVAR) { G->val += count; }
YY_LOCAL(void) yyPop(GREG *G, char *text, int count, yythunk *thunk, YY_XTYPE YY_XVAR)  { G->val -= count; }
YY_LOCAL(void) yySet(GREG *G, char *text, int count, yythunk *thunk, YY_XTYPE YY_XVAR)  { G->val[count]= G->ss; }

#endif /* YY_PART */

#define YYACCEPT        yyAccept(G, yythunkpos0)

YY_RULE(int) yy_Lust(GREG *G); /* 1 */

YY_ACTION(void) yy_1_Lust(GREG *G, char *yytext, int yyleng, yythunk *thunk, YY_XTYPE YY_XVAR)
{
  yyprintf((stderr, "do yy_1_Lust\n"));
   gotLust(core->this) ;
}

YY_RULE(int) yy_Lust(GREG *G)
{  int yypos0= G->pos, yythunkpos0= G->thunkpos;
  yyprintf((stderr, "%s\n", "Lust"));  if (!yymatchString(G, "lust")) goto l1;  yyDo(G, yy_1_Lust, G->begin, G->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "Lust", G->buf+G->pos));
  return 1;
  l1:;	  G->pos= yypos0; G->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Lust", G->buf+G->pos));
  return 0;
}

#ifndef YY_PART

typedef int (*yyrule)(GREG *G);

YY_PARSE(int) YY_NAME(parse_from)(GREG *G, yyrule yystart)
{
  int yyok;
  if (!G->buflen)
    {
      G->buflen= 1024;
      G->buf= YY_ALLOC(G->buflen, G->data);
      G->textlen= 1024;
      G->text= YY_ALLOC(G->textlen, G->data);
      G->thunkslen= YY_STACK_SIZE;
      G->thunks= YY_ALLOC(sizeof(yythunk) * G->thunkslen, G->data);
      G->valslen= YY_STACK_SIZE;
      G->vals= YY_ALLOC(sizeof(YYSTYPE) * G->valslen, G->data);
      G->begin= G->end= G->pos= G->limit= G->thunkpos= 0;
    }
  G->pos = 0;
  G->begin= G->end= G->pos;
  G->thunkpos= 0;
  G->val= G->vals;
  yyok= yystart(G);
  if (yyok) yyDone(G);
  yyCommit(G);
  return yyok;
  (void)yyrefill;
  (void)yymatchDot;
  (void)yymatchChar;
  (void)yymatchString;
  (void)yymatchClass;
  (void)yyDo;
  (void)yyText;
  (void)yyDone;
  (void)yyCommit;
  (void)yyAccept;
  (void)yyPush;
  (void)yyPop;
  (void)yySet;
}

YY_PARSE(int) YY_NAME(parse)(GREG *G)
{
  return YY_NAME(parse_from)(G, yy_Lust);
}

YY_PARSE(GREG *) YY_NAME(parse_new)(YY_XTYPE data)
{
  GREG *G = (GREG *)YY_CALLOC(1, sizeof(GREG), G->data);
  G->data = data;
  return G;
}

YY_PARSE(void) YY_NAME(parse_free)(GREG *G)
{
  YY_FREE(G);
}

#endif


// We get the parser object as an argument
int decadenceParse(void *this) {

    GREG *G = YY_ALLOC(sizeof(GREG), 0);
    G->buflen = 0;

    // let's initialize the state
    struct _ParserState state = { this };
    G->data = &state;

    while (yyparse(G)) {}

    return 0;

}

