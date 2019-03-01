//room: /d/mingjiao/neishi.c
inherit ROOM;

void init();
void create()
{
        set("short","明教內室");
        set("long", @LONG
這裏是明教內室。小小桌前的窗外，望出去是連綿萬里的巍巍昆
侖。窗櫺門扇均雕製得美侖美奐，精巧異常桌前端坐一個亮麗女孩，
你乍一見驚異她的美貌，不禁輕輕叫出聲來。
LONG );
        set("exits",([
            "out" : __DIR__"dadian",
        ]));
        set("no_fight",0);
        set("no_beg","1");
        set("objects",([
            CLASS_D("mingjiao")+"/xiaozhao":1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}