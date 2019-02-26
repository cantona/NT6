// Room: /d/taishan/daizong.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "岱宗坊");
        set("long", @LONG
岱宗坊，又名玲瓏坊，位於泰安縣城以北約一里，坊建於台基上，
四柱三門式，康熙大帝撰書楹聯：“峻極於天，贊化體元生萬物；帝出
乎震，赫聲濯靈鎮東方。”此處是登泰山的入口。相傳當年碧霞元君被
姜子牙戲弄，誘她投擲繡花鞋以定泰山地界，結果碧霞元君只能把繡花
鞋從山頂擲到此處。從此泰山便以此為起點。
　　坊東豐都廟，祀豐都大帝，配以冥府十王。坊北三皇廟，祀伏羲、
神農、黃帝，配以八蜡神。坊西建封院，宋政和年間改為升元觀，祀東
嶽福神東華帝君。坊內松柏鬱郁，奇石林立，溪泉爭流。
LONG );
        set("exits", ([
                "northup" : __DIR__"baihe",
                "south"   : __DIR__"daimiao",
                "west"    : "/d/huanghe/huanghe5",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("no_fight", "1");
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 60);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}