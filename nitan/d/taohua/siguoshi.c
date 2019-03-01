inherit ROOM;

void create()
{
    set("short", "思過室");
    set("long", @LONG
這是桃花島上供本門弟子閉門思過的地方。屋裡僅僅放著
張床，顯得空盪盪的。四面則是光禿禿的牆壁，看上去黑黝黝
的，原來卻是鐵築的。靠門的地方有一小洞，洞邊放著一只碗。
往東是一間不起眼的小屋。
LONG);
        set("exits", ([
                "west" : __DIR__"houyuan",
                "east" : __DIR__"xiuxishi",
        ]));
        setup();
}