top_srcdir = .

CLIENT  = client
TARGETS = $(CLIENT)
OBJS    = Servant.o
COBJS   = Client.o
SRCS    = $(OBJS:.o=.cpp) \
          $(COBJS:.o=.cpp)
INCPATH = .

SLICE_SRCS = Servant.ice

include $(top_srcdir)/config/Make.rules

CPPFLAGS := $(addprefix -I, $(INCPATH)) $(CPPFLAGS)

$(CLIENT): $(OBJS) $(COBJS)
	rm -f $@
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(COBJS) $(LIBS)

docs:
	mkdir -p ref
	doxygen Doxyfile
	cp -rf ../doxygen-style/* ref/instrumentSim/html/
	doxygen pygtk/Doxyfile
	cp -rf ../doxygen-style/* ref/pygtk/html/
	doxygen pyqt/Doxyfile
	cp -rf ../doxygen-style/* ref/pyqt/html/
	doxygen pyroot/Doxyfile
	cp -rf ../doxygen-style/* ref/pyroot/html/
	doxygen tkinter/Doxyfile
	cp -rf ../doxygen-style/* ref/tkinter/html/
