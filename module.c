#include "module.h"
#include "parser.tab.h"
#include "scanner.h"

module *
new_module_from_stdin()
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = stdin;
	return mod;
}

module *
new_module_from_file(const char *filename)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = fopen(filename, "r");
	return mod;
}

module *
new_module_from_string(char *src)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = fmemopen(src, strlen(src)+1, "r");
	return mod;
}

void
delete_module(module *mod)
{
	if (mod->rt != NULL) {
	//	delete_sexp_node(mod->rt);
	}
	fclose(mod->src);
	free(mod);
}

int
parse_module(module *mod)
{
	yyscan_t sc;
	int res;
	extern int yydebug ;
	yylex_init(&sc);
	yyset_in(mod->src, sc);
	//yydebug = 1;
	res = yyparse(sc, mod);
	//yylex_destroy(sc);

	if (res == 0) {
	//	print_node_sexp(mod->root);
	}

	return res;
}

void
ReturnStmtPrint(ReturnStmtClause *rt, char *in)
{
  OrderByStmtClause *odb = rt->odb;
  char *str = in;
  if (rt->hasDistinct)
  {
    sprintf(str,"SELECT DISTINCT ");
    str  += 16;
  }
  else
  {
	  sprintf(str,"SELECT ");
    str += 7;
  }

	ListCell *retcolCell = NULL;
  List *retcolList = NIL;

  retcolList = rt->returnCols;
  foreach(retcolCell,retcolList)
  {
    ReturnCols *retcol = (ReturnCols *) lfirst(retcolCell);
    if (retcol->hasFunc && retcol->hasDistinct)
    {
      sprintf(str,"%s(DISTINCT %s) ",retcol -> funName, retcol -> colname);
      str += strlen(retcol -> funName) + strlen(retcol -> colname) + 12;
    }
    else if(retcol->hasFunc && !retcol->hasDistinct)
    {
      sprintf(str,"%s(%s) ",retcol -> funName, retcol -> colname);
      str += strlen(retcol -> funName) + strlen(retcol -> colname) + 3;
    }
    else
    {
      sprintf(str,"%s ", retcol -> colname);
      str += strlen(retcol -> colname) + 1;
    }
    
    if (retcol->hasAlias)
    {
      sprintf(str,"AS %s ",retcol->colAlias);
      str += strlen(retcol->colAlias) + 4;
    }
    *str++ = ',';
  }		
  *--str = 0;
  if(rt->hasOrderBy) /*Order By ... DESC */
  {
    if (odb->ascDesc == 'A')
    {
      sprintf(str,"\nORDER BY %s ASC ",odb->orderByColname);
      str += strlen(odb->orderByColname) + 15;
    }
    else if (odb->ascDesc == 'D')
    {
      sprintf(str,"\nORDER BY %s DESC ",odb->orderByColname);
      str += strlen(odb->orderByColname) + 16;
    }
    else
    {
      sprintf(str,"\nORDER BY %s ",odb->orderByColname);  
      str += strlen(odb->orderByColname) + 11;
    }
  }
  if(rt->hasLimit)
    sprintf(str,"LIMIT %ld",rt->limitNum);
}

