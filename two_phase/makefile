# コンパイラ
CC  = g++
# コンパイルオプション
CFLAGS    =
# 実行ファイル名
TARGET  = two_phase
# 基本動作のソースコードが置かれているディレクトリ
BASDIR	= ../basic_source/
# index操作のソースコードが置かれているディレクトリ
INDDIR	= ../index/
# csv操作のソースコードが置かれているディレクトリ
CSVDIR	= ../operation_csv_source/
# コンパイル対象のソースコード
SRCS    = search.cpp
SRCS    += phase1_conf.cpp
SRCS	+= $(BASDIR)Cube_function.cpp
SRCS	+= $(BASDIR)Search_function.cpp
SRCS	+= $(BASDIR)move.cpp
SRCS	+= $(INDDIR)index.cpp
SRCS	+= $(CSVDIR)readCSV.cpp
# オブジェクトファイル名
OBJS    = $(SRCS:.cpp=.o)
 
# インクルードファイルのあるディレクトリパス
INCDIR  = -I$(BASDIR)
INCDIR	+= -I$(INDDIR)
INCDIR	+= -I$(CSVDIR)
 
# ライブラリファイルのあるディレクトリパス
LIBDIR  = 
 
# 追加するライブラリファイル
LIBS    = 

# ターゲットファイル生成
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)
	
# オブジェクトファイル生成
$(BASDIR)%.o: $(BASDIR)%.cpp
	g++ $(INCDIR) -c -o $@ $<

$(INDDIR)%.o: $(INDDIR)%.cpp
	g++ $(INCDIR) -c -o $@ $<

$(CSVDIR)%.o: $(CSVDIR)%.cpp
	g++ $(INCDIR) -c -o $@ $<

search.o: search.cpp
	g++ $(INCDIR) -c search.cpp -o search.o
	
phase1_conf.o: phase1_conf.cpp
	g++ $(INCDIR) -c phase1_conf.cpp -o phase1_conf.o

# "make all"で make cleanとmakeを同時に実施。
all: clean $(OBJS) $(TARGET)
# .oファイル、実行ファイル、.dファイルを削除
clean:
	-rm -f $(OBJS) $(TARGET) *.d