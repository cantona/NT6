inherit ROOM;

void create()
{
        set("short", "忘憂谷");
        set("long", @LONG
這裏乃是大輪寺外一處僻靜所在，四下絕無人跡。前前後後，大
大小小几百座佛塔，被白得耀眼的雪被披蓋着。銀白色的山野、雪地
裏閃耀着紅色和藍色的光帶，五彩繽紛，迷宮樣的瓊樓仙閣在你眼前
出現。南面一條小徑不知通往何處。
LONG );
        set("exits", ([
                "westup" : __DIR__"sroad8",
                "eastup" : __DIR__"sroad9",
        ]));
        set("objects", ([
                __DIR__"npc/zhuoma" :1,
                __DIR__"npc/yangzong" :1,
                CLASS_D("xuedao") + "/shanyong" : 1,
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
