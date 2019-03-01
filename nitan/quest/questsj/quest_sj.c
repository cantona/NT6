// Created by Smallfish For HUAXIA@2004, 2004/4/24

#include <ansi.h>

#define CHECK_DIR(x)    ("/quest/questsj/" + x)
#define CHECK_HEAD      CHECK_DIR("head_obj")
#define CHECK_ARMOR     CHECK_DIR("armor_obj")
#define CHECK_CLOTH     CHECK_DIR("cloth_obj")
#define CHECK_SWORD     CHECK_DIR("sword_obj")
#define CHECK_BLADE     CHECK_DIR("blade_obj")
#define CHECK_HAMMER    CHECK_DIR("hammer_obj")
#define CHECK_STAFF     CHECK_DIR("staff_obj")
#define CHECK_KNOWLEDGE CHECK_DIR("knowledge_obj")
#define CHECK_MIJI      CHECK_DIR("miji_obj")


mapping *quest = ({
        ([
                "id":                 "HEAD_OBJ",
                "name":               "頭胸護具、飾品",
                "msg0":               "武林同盟最近準備培訓一批女殺手，缺少頭部護具、頭飾、胸飾等物品，",
                "msg1":               "據報白駝山打算進攻中原，武林同盟必須未雨綢繆，最近頭部護具、頭飾、胸飾等物品緊缺，",
                "msg2":               "武林同盟庫房物資缺乏，尤其是頭部護具、頭飾、胸飾等物品，",
                "msg3":               "頭部、胸部是人體要害，一定要防護妥當，頭部護具、頭飾、胸飾等物品甚為緊要！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "件",
                "check_file":         CHECK_HEAD,
                "type":               "收",
        ]),
        ([
                "id":                 "ARMOR_OBJ",
                "name":               "身體護具",
                "msg0":               "最近江湖糾紛不斷，我們的身體護具等物資消耗很大，",
                "msg1":               "據報白駝山打算進攻中原，武林同盟必須未雨綢繆，",
                "msg2":               "上次去會見一位老友，看到他門下弟子護甲齊整，看來我們也要整頓一下，",
                "msg3":               "武林同盟新到了一大批兵器，現在身體護具等物資相較而言頗為緊缺，",
                "max_num":            35,
                "min_num":            25,
                "unit":               "件",
                "check_file":         CHECK_ARMOR,
                "type":               "收",
        ]),
        ([
                "id":                 "CLOTH_OBJ",
                "name":               "衣服",
                "msg0":               "最近新來了一幫兄弟，個個都很窮，連一件象樣的衣服都沒有，",
                "msg1":               "前陣子安排一幫兄弟去西荒之地完成一個任務，結果個個搞得衣衫襤褸回來了，",
                "msg2":               "這天氣有些反常，看來就要換季了，",
                "msg3":               "武林同盟庫房物資缺乏，尤其缺少衣服！",
                "max_num":            50,
                "min_num":            30,
                "unit":               "件",
                "check_file":         CHECK_CLOTH,
                "type":               "收",
        ]),
        ([
                "id":                 "SWORD_OBJ",
                "name":               "劍器",
                "msg0":               "劍乃百兵之首，兄弟們雖說不需人人都精通劍法，但也得熟知劍道，",
                "msg1":               "最近我剛創出一個威力巨大的劍陣，正準備安排人手演練一番，",
                "msg2":               "學武可以強身鍵體，雖然是老百姓也應該會個一招兩式，武林同盟最近準備開個免費培訓班，",
                "msg3":               "前天晚上武林同盟兵器庫居然失竊！真是豈有此理！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "柄",
                "check_file":         CHECK_SWORD,
                "type":               "收",
        ]),
        ([
                "id":                 "BLADE_OBJ",
                "name":               "刀器",
                "msg0":               "俗話說快刀斬亂麻，行走江湖的話，還是用刀比較暢快淋漓！",
                "msg1":               "弟兄們最近日子過得安逸，刀法也生疏了不少，得敦促他們好好練習練習，",
                "msg2":               "對付仇家最暢快的就是亂刀齊下剁為肉泥，有個家伙老跟我作對，我已經安排好了弟兄去料理他，",
                "msg3":               "我想了解一下江湖中目前使用刀法的人士，對刀法的研究究竟到了何種境界！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "柄",
                "check_file":         CHECK_BLADE,
                "type":               "收",
        ]),
        ([
                "id":                 "HAMMER_OBJ",
                "name":               "錘類兵器",
                "msg0":               "錘法是相當難練的一種武藝，我打算親自給弟兄們指點一下此門功夫，",
                "msg1":               "錘法要使的好，關鍵是兵器要設計的恰當！",
                "msg2":               "最近剛招募了一幫東北大漢，身高體壯，最是適合修煉錘法，",
                "msg3":               "我對大部分兵器也算頗有研究，只是對錘類兵器不甚明了！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "柄",
                "check_file":         CHECK_HAMMER,
                "type":               "收",
        ]),
        ([
                "id":                 "STAFF_OBJ",
                "name":               "棍、杖類兵器",
                "msg0":               "修煉武功，棍法是很好的奠基功夫，新來的兄弟必須好好掌握棍法，",
                "msg1":               "棍、杖向來是冷門兵器，我最近頗為空閒，準備對其好好研究一番，",
                "msg2":               "弟兄們日常操練，刀劍容易傷人，棍、杖最為合適！",
                "msg3":               "聽說最近江湖中頗多高手使用杖法，我也想研究一下棍法、杖法的深奧之處！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "根",
                "check_file":         CHECK_STAFF,
                "type":               "收",
        ]),
        ([
                "id":                 "KNOWLEDGE_OBJ",
                "name":               "知識類書籍",
                "msg0":               "武林同盟新建立一座藏經閣，準備收藏天下所有經書典籍，",
                "msg1":               "古人雲：活到老，學到老！我準備讀遍天下經書典籍，",
                "msg2":               "不知我可否稱得上學富五車、才高八鬥？不知我可否有未曾讀過的經書典籍？",
                "msg3":               "習武之人最緊要的就是修心養性，最近弟兄們大多心浮氣燥，得約束約束他們了！",
                "max_num":            30,
                "min_num":            20,
                "unit":               "本",
                "check_file":         CHECK_KNOWLEDGE,
                "type":               "收",
        ]),
        ([
                "id":                 "MIJI_OBJ",
                "name":               "武功秘笈",
                "msg0":               "武林同盟新建立一座藏經閣，準備收藏天下所有武功秘笈，",
                "msg1":               "少林有個藏經樓收藏了七十二般武功秘笈，我們武林同盟難道比少林略有遜色？",
                "msg2":               "我已經讀過無數武功秘笈，不知可有我未曾知曉的武技？",
                "msg3":               "將天下所有武功秘笈搜括囊中是我一生最大的宏願之一！",
                "max_num":            30,
                "min_num":            20,
                "unit":               "本",
                "check_file":         CHECK_MIJI,
                "type":               "收",
        ]),
});

mapping query_good()
{
        return quest[random(sizeof(quest))];
}
