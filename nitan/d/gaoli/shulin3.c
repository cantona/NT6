// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "樹林");
        set("long", @LONG
你走在一片樹林之中。這裡樹木茂盛，參天蔽日，非常涼快。北邊
是一個烽火台。再望南邊走，就是高麗的朝陽門了。有幾個官兵正在這
裡檢查來往的行人。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shulin2",
                "northup":__DIR__"dongfenghuotai",
        ]));
       setup();
        replace_program(ROOM);
}        
