// Room: /d/yueyang/dongtingmiao2.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "洞庭廟寢殿");
        set("long", @LONG
寢殿在洞庭廟主殿後面。寢殿為柳毅和小龍女並排坐像，大殿為單
檐歇山式建築。柳毅在洞庭湖畔為平民百姓做了很多好事，人們為了紀
念他，便在君山築起洞庭廟，塑起柳毅和龍女像。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"dongtingmiao1",
        ]));
        set("coor/x", -1660);
        set("coor/y", 2360);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}