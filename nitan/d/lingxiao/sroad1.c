inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
從這裡開始，就是上凌宵城的山路了。抬頭一望，雪峰高插
雲霄，看不見頂，自己站立之處，僅僅是在山腳高一點，卻已有
點“高處不勝寒”之感了。一路行來，雖還在山腳，卻已感覺到
寒氣逼人，路旁的樹上，全掛滿了白雪冰凌，一陣冷風吹來，已
讓人縮頭籠手。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "eastdown"  : __DIR__"boot",
                    "northup"  : __DIR__"sroad2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
