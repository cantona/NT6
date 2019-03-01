inherit ROOM;

void create()
{
        set("short", "地牢");
        set("long", @LONG
這裡是雪山寺內的一個陰暗、潮濕的牢房。你感到奇怪的是怎麼
會不時聽到一點怪聲卻怎麼也找不到人呢。
LONG );
        set("exits", ([
                "southup" : __DIR__"houyuan",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}