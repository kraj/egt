CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	-I$(top_srcdir)/include \
	-I$(top_builddir)/include \
	-isystem $(top_srcdir)/external/rapidxml \
	$(LIBPLANES_CFLAGS) \
	$(CAIRO_CFLAGS) \
	$(LIBDRM_CFLAGS) \
	$(TSLIB_CFLAGS) \
	$(LUA_CFLAGS) \
	$(GSTREAMER_CFLAGS) \
	$(LIBJPEG_CFLAGS) \
	$(LIBINPUT_CFLAGS) \
	$(LIBCURL_CFLAGS) \
	$(LIBRSVG_CFLAGS) \
	$(CODE_COVERAGE_CXXFLAGS)

CUSTOM_LDADD = $(LIBPLANES_LIBS) $(CAIRO_LIBS) $(LIBDRM_LIBS) $(TSLIB_LIBS) \
	$(LUA_LIBS) $(GSTREAMER_LIBS) $(LIBJPEG_LIBS) \
	$(LIBINPUT_LIBS) $(MAGIC_LIB) $(LIBRSVG_LIBS) $(LIBCURL_LIBS) \
	$(CODE_COVERAGE_LDFLAGS)

bin_PROGRAMS = snippets snippet0 snippet1 snippet2 \
	snippet3 snippet4 snippet5 snippet6 snippet7 \
	snippet8 snippet9 snippet10

snippets_SOURCES = snippets.cpp
nodist_snippets_SOURCES = $(BUILT_SOURCES)
snippets_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
snippets_LDADD = $(top_builddir)/src/libegt.la $(CUSTOM_LDADD)
snippetsdir = $(prefix)/share/egt/examples/snippets
snippets_DATA = $(wildcard $(top_srcdir)/examples/snippets/assets/*.png) \
	$(wildcard $(top_srcdir)/examples/snippets/assets/*.wav) \
	$(wildcard $(top_srcdir)/examples/snippets/assets/*.mp3)
snippets_LDFLAGS = $(AM_LDFLAGS)

snippet0_SOURCES = snippet0.cpp
snippet0_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
snippet0_LDADD = $(top_builddir)/src/libegt.la $(CUSTOM_LDADD)

snippet1_SOURCES = snippet1.cpp
snippet1_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
snippet1_LDADD = $(top_builddir)/src/libegt.la $(CUSTOM_LDADD)

snippet2_SOURCES = snippet2.cpp
snippet3_SOURCES = snippet3.cpp
snippet4_SOURCES = snippet4.cpp

snippet5_SOURCES = snippet5.cpp
snippet5_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
snippet5_LDADD = $(top_builddir)/src/libegt.la $(CUSTOM_LDADD)

snippet6_SOURCES = snippet6.cpp
snippet6_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
snippet6_LDADD = $(top_builddir)/src/libegt.la $(CUSTOM_LDADD)

snippet7_SOURCES = snippet7.cpp
snippet8_SOURCES = snippet8.cpp
snippet9_SOURCES = snippet9.cpp

snippet10_SOURCES = snippet10.cpp
snippet10_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
snippet10_LDADD = $(top_builddir)/src/libegt.la $(CUSTOM_LDADD)
