inherit ROOM;

void create()
{
        set("short", "回春居");
        set("long", @LONG 
這就是凌霄城中醫術最高明的戴大夫所開的回春居，一進這
裏，就聞到一股刺鼻的藥味，只見房中擺滿了大大小小的箱籠藥
櫃。一名鬚髮皆白的老人坐在桌旁，正在替一人把脈。旁邊牆上
貼着一張張條幅(tiaofu)，都是被閻大夫治好了的病人送的。
LONG );
        set("item_desc", ([
                "tiaofu" : "華佗再世,扁雀重生。\n",
        ]));
        set("objects", ([
                __DIR__"npc/daifu" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"iceroad2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
