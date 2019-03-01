// Room: /d/yanping/yanshoumen.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "延壽門");
        set("long", @LONG
延壽門是延平府南門，門高可兩丈，青磚砌就，上壘敵樓，即名延
壽樓。國姓爺鄭成功為救隆武天子的駕，曾登陴督戰。清人有詩：“虎
踞竣(山曾)此一關，建瓴高屋俯千灣。歸雲峽口三溪水，橫翠峰前百丈
山。忠定謫來官舍冷，龜山老去講堂閒。垂虹閣向龍津倚，燭漢星光隱
照顏。”門外浮橋通往西溪南岸的九峰山。
LONG );
        set("exits", ([
                "north"     : __DIR__"road2",
                "southdown" : __DIR__"fuqiao2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing"    : 2,
        ]));
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}