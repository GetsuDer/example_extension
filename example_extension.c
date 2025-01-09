#include "postgres.h"
#include "commands/explain.h"
#include "executor/executor.h"

PG_MODULE_MAGIC;

static ExecutorStart_hook_type prev_ExecutorStart = NULL;
static void example_ExecutorStart(QueryDesc *queryDesc, int eflags);

void
_PG_init(void)
{
	prev_ExecutorStart = ExecutorStart_hook;
	ExecutorStart_hook = example_ExecutorStart;
}

static void
example_ExecutorStart(QueryDesc *queryDesc, int eflags)
{
	ExplainState *es = NewExplainState();

	if (prev_ExecutorStart)
		prev_ExecutorStart(queryDesc, eflags);
	else
		standard_ExecutorStart(queryDesc, eflags);

	ExplainBeginOutput(es);
	ExplainPrintPlan(es, queryDesc);
	ExplainEndOutput(es);

	elog(LOG, "Query plan from ExecutorStart hook: %s", es->str->data);
}
