inherit ROOM;

void create()
{
        set("short", "清心閣");
        set("long", @LONG
這是寺中諸僧前去後院參修之前清心凈欲的地方。閣中只有地面
放有幾個蒲團，除此之外別無它物，確然是個清靜之處。
LONG );
        set("exits", ([
                "south": __DIR__"doushuai",
                "north" : __DIR__"wuwujing",
        ]));
        set("objects",([
                __DIR__"npc/xiaoshami" : 2,
        ]));
        set("sleep_room", 1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}