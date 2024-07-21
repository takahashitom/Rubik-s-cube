# コンパイラ
CC  = g++
# コンパイルオプション
CFLAGS    =
# 実行ファイル名
TARGET  = dfs
# 基本動作のソースコードが置かれているディレクトリ
BASDIR	= ../basic_source/
# コンパイル対象のソースコード
SRCS    = dfs.cpp
SRCS	+= $(BASDIR)Cube_function.cpp
SRCS	+= $(BASDIR)Search_function.cpp
SRCS	+= $(BASDIR)move.cpp
# オブジェクトファイル名
OBJS    = $(SRCS:.cpp=.o)
 
# インクルードファイルのあるディレクトリパス
INCDIR  = -I$(BASDIR)
 
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

dfs.o: dfs.cpp
	g++ $(INCDIR) -c dfs.cpp -o dfs.o

# "make all"で make cleanとmakeを同時に実施。
all: clean $(OBJS) $(TARGET)
# .oファイル、実行ファイル、.dファイルを削除
clean:
	-rm -f $(OBJS) $(TARGET) *.d