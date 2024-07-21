# コンパイラ
CC  = g++
# コンパイルオプション
CFLAGS    =
# 実行ファイル名
TARGET  = create_transition_table
# 基本動作のソースコードが置かれているディレクトリ
BASDIR	= ../basic_source/
# index操作のソースコードが置かれているディレクトリ
INDDIR	= ../index/
# csv操作のソースコードが置かれているディレクトリ
CSVDIR	= ../operation_csv_source/
# コンパイル対象のソースコード
SRCS    = create_transition_table.cpp
SRCS	+= $(BASDIR)Cube_function.cpp
SRCS	+= $(BASDIR)move.cpp
SRCS	+= $(INDDIR)index.cpp
SRCS	+= $(CSVDIR)writeCSV.cpp
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

create_transition_table.o: create_transition_table.cpp
	g++ $(INCDIR) -c create_transition_table.cpp -o create_transition_table.o

# "make all"で make cleanとmakeを同時に実施。
all: clean $(OBJS) $(TARGET)
# .oファイル、実行ファイル、.dファイルを削除
clean:
	-rm -f $(OBJS) $(TARGET) *.d