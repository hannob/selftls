These Patches disable the random number generator in OpenSSL and will
cause it to only output 1 all the time.

WARNING: This is not intended to be used in a production version. It is
only useful for fuzz testing.
