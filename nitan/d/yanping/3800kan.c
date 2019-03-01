// Room: /d/yanping/3800kan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "三千八百坎");
        set("long", @LONG
自古入閩無敞途。往來貨運全靠肩挑背扛，逶迤入閩，車馬不通。
這段古道號稱“三千八百坎”，寬僅三尺，青石砌就，階如長龍，盤曲
蜿蜒，縈繞碧峰，甚為壯觀。行商頭腳相繼，直達峰頂古堡。相傳老農
王堂選籌資多年，親率工匠用了十年時間勘察設計，鑿巖削壁，舖築石
階，重修古道，乃成坦途。薩鎮冰勒石“義聲載道”于中途。故老相傳：
“三千八百坎，坎坎有黃金”。
    由此下到坎底衍仙山麓，就是延平府城了。
LONG );
        set("exits", ([
                "northup"   : __DIR__"banyanting",
                "southdown" : __DIR__"yidao3",
        ]));
        set("objects", ([
                "/d/taishan/npc/tiao-fu" : 2,
        ]));
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}