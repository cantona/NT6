inherit ROOM;

void create()
{
        set("short", "打鐵鋪");
        set("long", @LONG
這就是凌霄城的刀劍鋪。走進這裏，寒氣侵體，好像比外面
還要冷。仔細一看，牆上掛滿了大大小小、形形色色的刀劍，一
柄柄寒光閃閃，全是上品。店主軒轅蒼翼看到有人進來，立刻殷
勤地迎上前來。
LONG );
        set("exits", ([
                "east" : __DIR__"iceroad2",
        ]));
        set("objects", ([
                "/d/city/npc/smith": 1,
        ]));
        setup();
        replace_program(ROOM);
}
