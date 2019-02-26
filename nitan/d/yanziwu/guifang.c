//ROOM: /d/yanziwu/guifang.c

inherit ROOM;

void create()
{
        set("short", "靚閨房");
        set("long",@LONG
這裏就是包三先生的寶貝乖女兒包不靚的閨房了。包小姐雖然年方
幼齒，可是擺弄起她那個在江湖上誰也不怕的爹來卻是絕活。真讓人相
信“一物降一物”的天理。不過也同時附帶證明了另一條天理：“惡人
自有惡人磨”。
LONG );
        set("exits", ([
                "east": __DIR__"jinfeng",
        ]));
        set("objects", ([
                __DIR__"npc/baobuliang": 1,
        ]));
        set("coor/x", 740);
        set("coor/y", -1550);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}