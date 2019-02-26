// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "中軍大帳");
        set("long", @LONG
        
這是百濟駐軍所在的兵營的中軍大帳，正中一張帥案，上面放着十
二把令箭，後面坐着一位老將軍，兩旁的的將士各個盔明甲亮。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"yuanmen",
        ]));
       setup();
        replace_program(ROOM);
}        
