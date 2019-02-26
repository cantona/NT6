// Room: /d/playtown/biwuchang.c 比武場
// Build 199.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "比武場");
        set("long",
"這是玩家村裏的村民練武和過招的地方，時而會衝上兩個人來相互切\n"
"磋，大概是因為這裏是一個凹地的原因吧，這裏總是很大沒有什麼風，一\n"
"點點小小的動靜在這裏都會聽得清楚。不遠的地方埋着一個小石碑（bei）\n"
",似乎年代很久。\n"
);
        set("outdoors", "playertown");
        set("exits", ([
                "south"  : __DIR__"miao",
        ]));
        setup();
        replace_program(ROOM);
}