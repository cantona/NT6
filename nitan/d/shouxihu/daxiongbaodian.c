// Room: /yangzhou/daxiongbaodian.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","大雄寶殿");
        set("long",@LONG
寶殿面南三楹，迎面二層檐的屋脊上，立有“大雄寶殿”四字橫匾。
屋脊正中嵌寶鏡一面，迎面嵌“風調雨順”四字，背面嵌“國泰民安”
四字。
    大雄寶殿供奉三尊大佛，中為釋迦牟尼佛，東為藥師琉璃光佛，西
為極樂世界阿彌陀佛，釋迦牟尼佛兩側脅侍是他的兩大弟子，東立阿難，
西立迦葉。東西兩廂為十八羅漢，北廂分坐禪宗六祖。佛壇背後為泥塑
群像海島，上有觀音菩薩腳踩巨鰲立像，觀音四周有救八難的塑像。觀
音像兩旁有善財童子和龍女，整個畫面有大小塑像百零六尊。
LONG );
        set("exits", ([
                "east"  : __DIR__"qingkongge",
                "west"  : __DIR__"gulintang",
                "north" : __DIR__"cangjinglou",
                "south" : __DIR__"yongdao",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng" : 1,
        ]));
        set("coor/x", -30);
        set("coor/y", 170);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}