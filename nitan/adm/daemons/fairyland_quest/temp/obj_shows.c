//                標準描述長度示例                                   |
// 遊戲內簡易說明手冊
// by naihe  2002-11-05  于茂名

// 更新于 6:43 03-10-22   by naihe
// 最後更新 15:42 03-10-30 by naihe

inherit ITEM;

void create()
{
    set_name("『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 玩家手冊", ({"shou ce","ce"}));
    set_weight(10);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "這是一小本關于“幻境”遊戲的玩家說明手冊，輸入 <shows> 查看說明。\n");
        set("unit", "本");
        set("value", 0);
    }

    setup();
}

void init()
{
    add_action("do_shows","shows");
}

int do_shows(string arg)
{
    if(!arg) return notify_fail("你可以輸入頁數或類型來閱讀這些說明。例如 <shows 1> 或 <shows story>。

第1頁： 幻境遊戲背景劇情     <juqing>    或  <story>
第2頁： 『幽靈顯現』 劇情    <juqing2>   或  <story2>
第3頁： 遊戲進程及指令       <zhiling>   或  <cmds>
第4頁： 支線任務簡介         <renwu>     或  <job>
第5頁： 戰鬥系統及相關       <zhandou>   或  <fight>
第6頁： 各類NPC 簡介         <npc>
第7頁： 各類物品/工具簡介    <wupin>     或  <tools>
第8頁： 遊戲內地圖           <ditu>      或  <map>
第9頁： 技能、力量的保留與人物升級
第10 - 11頁：特別提示        <tishi1>    及 <tishi2>
第12頁： 最後的說明          <zuihou>    或  <last>

祝遊戲愉快！ :) \n");

    if(arg == "1" || arg == "juqing" || arg == "story")
    {
write("***************************************************************

『幻境﹒遙遠傳說之起緣』  背景劇情

    在此之前的一個未知的遙遠年代，這大地上寂寞荒涼，除了僅有人
煙的四個國家，分駐在這大地的四方。它們有著各自的繁華、能力及令
人艷羨的寶物，一直都各自安居樂業，大地上平靜而快樂著。

    但是終于有一天，它們之間爆發了戰爭，戰爭由寶物而起，我們卻
無從知曉那根本的因緣……四個國家由于戰爭而消亡了，而它們的寶物，
也消散在這茫茫的大地之上。\n");
write("
    時光變遷，這四個國度不復存在；終于，到了你與我生存的年代。
一個偶爾的機會，你來到了神秘的“迷失之寶物隱匿之林”，傳說這裡
隱匿著那遙遠年代時的四個國度的寶物，那些曾維持著它們在那荒涼土
地上安居的寶物，而又讓它們因此而消亡的寶物……你渴望在這片渺無
邊際的密林裡尋得它們，以求能夠得到它們所予你的啟示，重見那已逝
的古老國度的神秘光芒。

***************************************************************\n");
return 1; }

    if( arg == "2" || arg == "juqing2" || arg == "story2" )
    {
write("***************************************************************

『幻境﹒遙遠傳說之起緣﹒幽靈顯現』  劇情

    熱情的勇士仍在詭秘的密林中不懈尋找，而林中也日漸熱鬧，
各色人等穿梭往返，但卻一直徒勞無功。

    正當所有的人們都失望消散之時，一個月色幽朗的夜晚，你
在偶然的走動之中，竟來到了林中一處從未見到過的水潭之岸，
在岸邊精致幽雅的小亭前方，一柄粗大的權杖插在地上。你看著
權杖上刻著的小字，一股寒意從心底漸漸升起……

    幽靈之族，終于此時而始，來到了這個神秘的樹林之中！

***************************************************************\n");
return 1; }


    if(arg == "3" || arg == "zhiling" || arg == "cmds")
    {
write("***************************************************************
『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 遊戲進程、操作及各類介紹

    每一個進入幻境遊戲的玩家，都會得到一個物品：七星燈。它不允許
丟棄或給別人，並且你所有的遊戲內指令，都由它支持。

    你先要選擇一個國度來進入遊戲，每個國度的寶物不同，但都是被分
成了三個部分，你要一一找到，然後組合起來，才能夠得到真正完整的寶
物。寶物的其中兩部分散落在林子的任何一處，而最重要的一部分在一個
屬于你的臣民(chen min)身上。你向他打聽寶物的名字就能知道該怎麼做。\n");

write("
    遊戲裡以得分為主要目標，它並不限制你必須做什麼和必須不做什麼，
一切都是自由而隨意的。當你成功尋得屬于自己的寶物，並且把它帶離了
樹林（成功結束遊戲）的話，將會得到 1500 分的高額得分。而與怪物們
戰鬥、解答迷題、完成任務、拾取物品……這些都是得分的途徑。但是如
果你的氣息已經降至零點或以下，那麼即使有再多的得分，也將全部作廢。

    而遊戲的指令，請在進入遊戲後，輸入(help hj) 查看詳細的說明。
***************************************************************\n");
return 1; }

    if(arg == "4" || arg == "renwu" || arg == "job" )
    {
write("****************************************************************
『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 支線任務介紹

    在 『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 裡，除了尋找自己的寶物
之外，主要的得分途徑還有一個，這就是支線任務。由于在『幽靈顯現』
裡增加了許多個支線任務，並且它們都帶有一定的謎題性質，所以在這裡
不作過多的介紹，僅列出任務表（包括以前已有的任務）如下：

(1) ???? (謎題)：   可自選任務，無懲罰，高風險，小量得分及提高技能。
(2) ???? (謎題)：   自由任務，無懲罰，極高風險，得分極高。
(3) 藏劍生﹒珠寶客 ：
    之一：(公開)：  自由任務，無懲罰、風險，獲得極好武器。
    之二：(半謎題)：自由任務，無懲罰、風險，得分高。\n");

write("(4) 知識老人：(公開)：自由任務，有懲罰、小風險，難度大，得分較高。
(5) 精靈孩童：(公開)：自由任務，有懲罰，小風險，難度小，小量得分。
(6) 尋物精靈：(公開)：自由任務，無懲罰、風險，獲得極好物品。
(7) 蒙面人：  (公開)：強制任務，大量懲罰，無風險，無難度，得分少。

    完成的任務越多，不言而喻，你的得分將會越高。
****************************************************************\n");
return 1; }

    if( arg == "5" || arg == "zhandou" || arg == "fight" )
    {
write("****************************************************************

『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 怪物、戰鬥、技能介紹

    在 『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 裡，戰鬥系統與 MUD裡
我們習慣的方式不同，也與前集的有很大的差異。針對前集的缺點，在
『幽靈顯現』裡，戰鬥方式大幅度調整，如果是老玩家了，你將會感到
一份貼心的舒適。戰鬥系統、怪物、技能、人物升級等詳細介紹，請在
進入遊戲後，輸入 (help hj)、(help hj npc)、(help hj pfm)、
(help hj yun)、(help hj lvup) 等指令查詢。\n");

write("
    遊戲裡的 力量值 十分重要，你的任何攻擊行為，和它都有直接的
聯系。但這是一項隱藏的數值，你無法知道具體它已經有多高。力量值
可通過空手攻擊、使用特殊物品、或其他特殊方法得到提高，有上限。

    並非所有的NPC都準許攻擊，請參看後文介紹。

****************************************************************\n");
return 1; }

    if( arg == "6" || arg == "npc")
    {
write("****************************************************************
『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 非玩家操作類人物(NPC)介紹

    1、自己的NPC
    每個進入遊戲的玩家都會對應一個不同的特殊npc，即臣民(chen min)。
他身上帶著你要找的寶物的最重要的那部分，你要向他打聽寶物的名字，
才能知道下一步該怎麼做。一定的時間到達後（約半小時），他就會消失，
這個時候你只能依靠特殊的物品「召喚之盒」，才有可能重新把他召來。
而另外的兩部分寶物，通過特殊物品「祈禱之石」，也有機會獲得。\n");

write("
    2、殺戮型NPC
    允許玩家攻擊。不同等級的這類型NPC的攻擊力、攻擊頻率、自身氣息等，
都不相同。攻擊NPC能夠得到遊戲裡的得分，殺死它們還有可能得到一些物品。
關于 NPC 的詳細資料，可在遊戲內使用 (help hj npc) 指令查詢。

    3、小精靈 遊戲的獎勵型NPC，有各種類型，能夠隨機予你不同的幫助。\n");

write("
    4、特殊類型 / 其他類型   這裡不作介紹。

    請注意，除了本人NPC之外，所有的NPC都是四處走動的。
****************************************************************\n");
return 1; }

    if(arg == "7" || arg == "wupin" || arg == "tools" )
    {
write("****************************************************************
『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 各類物品介紹
1、工具類
    定向水晶    可讓你知道自己身在何方，誤差 +-1
    飛翔之石    可讓你瞬間移動至某編號之地點，誤差 +-1
    脫離水晶    奈何的至愛之一，逃命必不可少的道具，無忙時使用限制
    回歸之鏡    立刻退出遊戲，得分有效（進入遊戲時間太短時無法使用）
    祈禱之石    祈禱隨機物品，有機會獲得屬于自己的寶物的部分
    召喚之盒    召喚隨機NPC，有機會召來自己的臣民
    發呆之旗    相當搞笑的道具之一，熱愛PK者必不可少
    驅逐之旗    相當搞笑的道具之一，也是奈何在這遊戲裡的至愛物品
    尋人水晶    輸入玩家的ID，你可以知道他在哪個地點裡(pk、組隊必備)
    窺探水晶    可以知道別人身上帶有哪些幻境裡的物品(pk必備)
    定位之儀    可以將一個地點定位，然後隨時快速地回到該處\n");
write("2、武器類 各類劍 及 各類水晶等，可讓你在戰鬥時更強大。使用它們的
          方法，請在遊戲內輸入 (help hj) 查詢。
3、果品類 普通果品  補充你在幻境裡的氣息
          試煉之果  可能增加力量或最大氣息\n");
write("4、技能石類  領會 <linghui> 它們，可以讓你學會技能或提升技能
5、其他 / 特殊類    用途神秘、多樣，不一一介紹。
****************************************************************\n");
return 1; }

    if(arg=="8" || arg=="ditu" || arg=="map")
    {
write("****************************************************************
『幻境﹒遙遠傳說之起緣﹒幽靈顯現』  遊戲地圖(地點標記號)

    “幽靈顯現”裡共有 60 個地點。

         □  2   3   4   5   6   7   8   9   10

         11  12  13  14  15  16  17  18  19  20

         21  22  23  24  25  26  27  28  29  30

         31  32  33  34  35  36  37  38  39  40

         41  42  43  44  45  46  47  48  49  50

         51  52  53  54  55  56  57  58  59  60

   允許橫、豎、斜走。方向為：上北下南左西右東 。

****************************************************************\n");
return 1; }

    if( arg == "9" )
    {
write("****************************************************************
『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 技能、力量的保留與人物升級

    在『幽靈顯現』裡，你在遊戲中積累的力量值以及所有的技能，都能夠得
到保留，即你在下一次進入遊戲時，不必從一個什麼技能都不懂、力量低微的
“弱小狀態”開始遊戲，而可以保留你大部分在之前通過練習而獲得的這些較
高的數值進入遊戲。

    保留的方法是：在任何一次成功遊戲後，兌換獎勵時選擇相應的項目即可。
注意，你必須要有相當高的得分，才能夠兌換這類的獎勵。一些補充說明，請
于退出遊戲的地點“回歸之路”輸入 <YEAH!!! sp> 查看。\n");

write("
    關于人物升級，請于遊戲內輸入 <help hj lvup> 或 <help hj levelup>
查看。人物的級別將會永久保存，並且不會像保留技能那樣每次進入遊戲都被
削減──但顯然的，人物的升級，需要更高的要求。

****************************************************************\n");
return 1; }

    if( arg == "10" || arg == "tishi1" )
    {
write("************************************************************
『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 一些遊戲提示（之一）

1.  選擇你的國度將對遊戲有什麼影響。

    各國度有自己的“特殊技能”，也有自己的“主動技能”。你
可以根據需要或者喜愛來選擇國度。關于這些技能，在遊戲內輸入
(help hj yun) 指令可查詢詳細說明。
***********************************************************\n");
return 1; }

    if( arg == "11" || arg == "tishi2" )
    {
write("
************************************************************

『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 一些遊戲提示（之二）

2.  啦啦啦地哼歌的小精靈 ---- 教導你學會或提升技能
    嬉笑的小精靈 ------------ 幫助你恢復氣息
    唱採果兒的歌的小精靈 ---- 會從身上掉下許多果品
    唱找東西的歌的小精靈 ---- 幫助她找到東西，可以得到神人令\n");

write("
3.  當你總是無法找到你的寶物所屬的部分時，你可以嘗試用
    祈禱之石，它有機會讓你得到自己的寶物部分。
    當你總是無法找到你的臣民時，你可以嘗試用召喚之盒，它
    有機會將之召喚出現。

***********************************************************\n");
return 1; }



    if(arg == "12" || arg=="zuihou" || arg=="last")
    {
write("****************************************************************

『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 使用手冊之最後說明

    本遊戲由 神州巫師 奈何(naihe) 開發。如有建議或意見，
請 E-MAIL TO :  lovesb@21cn.com  奈何 收，或在 神州 內
使用 mto 發信給奈何收、或 post 于留言版內。

    遊戲的獎勵，以遊戲出口處【回歸之路】裡公布的為準。

    奈何(naihe)   2002-11-05 于廣東茂名


    《幻境一﹒遙遠傳說之起緣﹒幽靈顯現》
    奈何(naihe)  2003年10月  于廣東茂名
    
    再次更新各類細節
    奈何(naihe)  2005年 9月  于廣東茂名

****************************************************************\n");
return 1; }



    write("輸入有誤。請直接輸入 <shows> 查正再試。\n");
    return 1;
}
