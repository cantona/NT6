// /d/beihai/yuexin.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "悦心殿");
        set("long", @LONG
這裏是永安寺西之悦心殿，殿內為五開間、西山灰瓦頂，是清帝引
見、理事之所。殿內非常安靜，只依稀可聞有僧人掃着落葉的聲音。殿
前有寬闊的月台，與慶宵樓相連殿內院中有一棵老樹，枝葉茂密。殿內
光線很暗，看不清楚有些什麼。
LONG
        );
        set("exits", ([
                "east"    : __DIR__"yongansi",
                "northup" : __DIR__"qingxiao",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -200);
        set("coor/y", 4080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}