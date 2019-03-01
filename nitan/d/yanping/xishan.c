// Room: /d/yanping/xishan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "西山");
        set("long", @LONG
西山屹立在府城中央，山頂就是州學。半山處，是一碑亭，亭聯
“獨先天下興州學，屹立西山勵後賢”。亭內是“南劍州重建州學記
碑” (bei)，碑文記述此地山川形勝，文章風流之盛事，追昔撫今，
感慨無限。
LONG );
        set("exits", ([
                "northup"   : __DIR__"zhouxue",
                "southdown" : __DIR__"road3",
        ]));
        set("item_desc", ([
                "bei" :
"
碑由黑頁巖雕成，圓首，篆額，高丈許，闊六尺，花崗巖龜趺座，
進士張致遠撰文，進士羅薦可書。

                    南劍州重建州學記

    延平郡治，當七閩之沖。而舊學跨西山，特踞形勝。九龍、雙
旌、演仙、文筆諸峰皆秀拔摩雲，環顧如列屏障。建、劍二水會而
南流。風雨晦暝，神物吼越，潭靜天開，想紫光隱隱牛鬥間。異時
偉人輩出，其冠巍科，躋憮仕，術業足以師世，循良忠烈足以動宸
極，而厭紳芴者相望也。......
"
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}