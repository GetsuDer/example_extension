MODULE_big = example_extension
OBJS = example_extension.o
EXTENSION = example_extension
DATA = example_extension--1.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
