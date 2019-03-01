inherit ROOM;

void create()
{
        set("short", "金刀王家");
        set("long", @LONG
這裡便是洛陽金刀王家的府邸，江湖上提起金刀無敵王元霸當真是無
人不知，無人不曉。只見這府邸房舍高大，朱紅漆的大門，門上兩個大銅
環，擦得晶光雪亮，八名壯漢垂手在大門外侍候。一進大門，只見樑上懸
著一塊黑漆大匾，寫著“見義勇為”四個金字，下面落款是河南省的巡撫
某人。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"wroad3",
        ]));
        set("objects", ([
                "/d/zhongzhou/npc/jiading" : 2,
        ]));
        setup();
        replace_program(ROOM);
}