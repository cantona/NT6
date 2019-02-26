inherit ROOM;

void create()
{
        set("short", "石崖客棧");
        set("long", @LONG
這裏是雪山山路上的一間客棧，雖然店面簡單樸實，平日也
不可能有什麼遊客來這雪域遊山玩水，但在這大雪山上，卻也是
獨一無二的客棧。到了這地方，要是不想被活活凍死在這萬里冰
川上，只怕還是得照顧一下這裏的生意。所以這家客棧倒也是生
意興隆。
LONG );
        set("outdoors", "lingxiao");
        set("exits", ([
                "west" : __DIR__"shiya",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
                "/clone/npc/walker" : 1,
                __DIR__"npc/dizi" : 2,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
