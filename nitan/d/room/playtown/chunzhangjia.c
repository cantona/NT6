// Room: /d/playtown/chunzhangjia.c 村長家
// Build 199.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "村長家");
        set("long",
"你走進來便覺得這裏與其他村裏人的居所有所不同，明顯在門面上氣\n"
"派了許多，兩張暗紅色的桐木長椅將一張茶几夾在中間，上面掛着一副大\n"
"大的財神畫像，一副對聯(duilian)由於時間悠久，早已看不太清晰，但\n"
"那橫幅仍然十分顯眼，赫然寫道“財源滾滾”。\n"
);

//      set("no_clean_up", 0);
        set("item_desc",([
                "duilian"        :        "上面已經看不太清楚了，只模模糊糊地認得清幾個字。\n",
        ]));
        
        set("exits", ([
                "east"  : __DIR__"road1",
                "west"  : "/d/room/xiaoyuan",
        ]));
        setup();
        replace_program(ROOM);
}