// Room: /d/yueyang/xiangfeici3.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "湘妃祠正殿");
        set("long", @LONG
正殿上方，懸掛有一塊黑底金字匾，上書“淵德侯”。因為相傳娥
皇女英歿水後，被天帝封神為“淵德後”，後張之洞修復湘妃廟時，尊
湘妃二神為“淵德侯”，故有此匾。走進正殿，香霧繚繞，大殿內台上
供奉有二妃塑像，四尊侍女塑紛立兩旁。據祠裏的人講，二妃塑像剛供
上去時是面帶笑容，可是，供了幾年，如今二妃皆由笑容轉變為悽悽含
淚神情。此中真味誰識？
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"xiangfeici2",
        ]));
        set("coor/x", -1660);
        set("coor/y", 2330);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}