// shimen.c 洞門


inherit ROOM;

void create()
{
        set("short", "石門");
        set("long", @LONG
這裏已是甬道盡頭，面前一道厚重的石門。門上刻着三個斗大的
古篆：「俠客行」。年深日久，那筆劃的凹下之處都積滿了青苔，越
發顯得滄桑，你心中的敬意油然而生。
    裏面是一塊大石壁，在石壁下好像有很多人。
LONG );
        set("exits", ([
                "enter" : __DIR__"shibi",
                "north" : __DIR__"yongdao3",
        ]));
        set("objects", ([
                __DIR__"npc/dizi3" : 1]));
        set("coor/x", -3080);
        set("coor/y", -22130);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}