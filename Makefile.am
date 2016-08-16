ACLOCAL_AMFLAGS = -I m4

SUBDIRS = ReverseAD

TESTS=ReverseAD/test/regression/test_identity\
      ReverseAD/test/regression/test_square\
	  ReverseAD/test/regression/test_quad\
	  ReverseAD/test/regression/test_param\
	  ReverseAD/test/regression/test_checkpointing\
	  ReverseAD/test/regression/test_single_forward\
	  ReverseAD/test/regression/test_multi_forward

test:
	cd ReverseAD; $(MAKE) test

.PHONY: test
