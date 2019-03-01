// Room: /d/yueyang/liuyijing.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "柳毅井");
        set("long", @LONG
柳毅井，亦稱桔井。它位于君山龍口內的龍舌的根部。唐代李朝威
寫的《柳毅傳書》的故事 (story)，就發生在這裡。井旁有古桔一株，
大“五六圍”，枝幹奇古。相傳為柳傳書之處。井入口丈許，有片石作
底，鑿數孔以通泉，石下深不可測。古老相傳，此井直通太湖。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("item_desc", ([
                "story" : "
    唐儀鳳年間，書生柳毅赴京應考落第，歸經涇陽，偶遇滿臉淚痕的
牧羊女。柳毅上前詢問得知，該女為洞庭龍女下嫁涇陽君，受其殘暴虐
待至此。他受龍女之托，送信至君山，找到桔井，在井邊的桔樹上敲擊
三下，守門的巡海神就將他接進了龍宮。見龍君，遞上書信，又訴龍女
苦。龍君小弟錢塘君暴怒，作百丈赤龍，徑往涇陽，滅涇陽君，接回龍
女，幾經曲折招柳毅為婿的故事。\n"
        ]));
        set("exits", ([
                "east"      : __DIR__"liuyiting",
                "southup"   : __DIR__"longsheshan",
                "northeast" : __DIR__"xiaolu5",
        ]));
        set("coor/x", -1690);
        set("coor/y", 2310);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}