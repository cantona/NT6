inherit ROOM;

void create()
{
        set("short", "頭天門");
        set("long", @LONG
只見有石梯無數通往山巔，一座石坊上寫著頭天門三個大字，這
是攀登武當絕頂天柱峰的起點。
LONG );
        set("exits", ([
                "north" : __DIR__"huixianqiao",
                "southup" : __DIR__"ertiangate",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -390);
        set("coor/z", 150);
        setup();
        replace_program(ROOM);
}