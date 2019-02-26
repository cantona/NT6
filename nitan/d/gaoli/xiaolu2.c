// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "小路");
        set("long", @LONG
你走在一條小路之上。再往西邊走就是高麗的一個烽火台了。烽火
台用來傳遞軍情。不時有幾個官兵從這裏走過，檢查着來往的行人。南
邊大海的波濤聲，更增添了幾分雄壯的氛圍。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"xiaolu1",
                "westup":__DIR__"fenghuotai",
                "northdown":__DIR__"zhuangjiadi",
        ]));
       setup();
        replace_program(ROOM);
}        
