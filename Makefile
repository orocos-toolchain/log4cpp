.PHONY: docs

docs:
	doxygen doxygen.config

clean:
	rm -r doc/*
