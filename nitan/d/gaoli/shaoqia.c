// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "哨卡");
        set("long", @LONG
        
你走在青石大道，來到一個哨卡，你還沒有靠近，有人大喊叫你停
步，你看見士兵弓上的箭，你趕緊轉身向後走。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                //"north" : __DIR__"tulu2",
                "southwest" : __DIR__"sanchalu",
        ]));
       setup();
        replace_program(ROOM);
}        
