inherit ROOM;

void create()
{
          set ("short", "竹林");
        set("long", @LONG
一陣清涼從頭頂碧綠的竹梢傾斜下來，幾點金色的光斑透過竹葉
在地上跳動，風過處，刷刷的聲響隨風而遠去，在竹林的中間被人開
出了一片空地，中央是一間小茅屋。
LONG );

          set("outdoors", "kaifeng");
          set("exits", ([
                  "enter" : __DIR__"zhulin1",
                  "west":__DIR__"fanta",
        ]));
	set("coor/x", -5020);
	set("coor/y", 2140);
	set("coor/z", 10);
	setup();
          replace_program(ROOM);
}