# CustomScan compatibility with ExplainPrintPlan
## What is this repo?
This is a very simple postgres extension.
Its only purpose is to call ExplainPrintPlan in ExecutorStart hook.

## What is this for?
This is useful for reproducing and debugging problems with CustomScans.
Pretty often CustomScans do not expect their ExplainCustomScan method to be called outside of usual EXPLAIN query.
But this method will be called from ExplainPrintPlan.
ExplainPrintPlan is used by some extensions to provide additional statistics about queryes.
This may lead to unexpected results.

## How to use
Set PATH to contain pg_config. Build and install the extension:

```
make USE_PGXS=1
make USE_PGXS=1 install
```

Add example_extension to shared_preload_libraries:

``
shared_preload_libraries = 'example_extension'
``

Now every ExecutorStart call will add 
``
Query plan from ExecutorStart hook: ***
``
In your logfile.
