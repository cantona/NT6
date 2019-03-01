// Room: /d/yanping/gubao.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "古堡");
        set("long", @LONG
仰望坎頂，視若關堡雄鎮雲天，關口為石拱門，內有一木構亭榭和
宋代的石砌古堡。堡內懸掛大總統曹錕題贈重修古道的邑人王堂選“義
問宣昭”木匾。古堡東面拱門前有六株千年柳杉，相傳是楊八妹的哨兵，
經仙人點化而矗立于此，其枝葉招展，橫亙數裡，蔚為壯觀，即使遠在
延平城東，也可瞥見其挺拔入雲的雄姿。登臨坎頂，可飽覽群山秀色。
放眼遠眺，城區民舍鱗次櫛比，閩江之水如銀帶環繞，氣派雄偉。古人
曰：“晨觀日出，延平城郭增絢麗；暮看夕落，百裡梯田披彩霞。”
LONG );
        set("exits", ([
                "west"      : __DIR__"mangdangshan",
                "southwest" : __DIR__"yanxianshan",
                "northdown" : __DIR__"yidao2",
                "southdown" : __DIR__"banyanting",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}