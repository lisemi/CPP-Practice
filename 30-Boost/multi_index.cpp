/**
boost 多索引容器的一般使用
这里使用google 的gmock 库来验证对boost 多索引模板的使用，并验证。
这里是手敲的，可能会有一些字符敲错的情况，编译错误的放，修改一下，同时链接gmock库就可以正常运行了。
当然还需要链接boost 的相关库
**/


#include <stdint.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/global_fun.hpp>


// 多索引的结构或者类
struct stru_AccountFeeIncre
{
	int64_t nAccountID;
	int32_t nGoodsID;
	int32_t nGoodsGroupID;
	int32_t nFeeMode;
	int32_t nTradeMode;
	double dFeeValue;
};

// 为索引的Key 定义一个标志类型，类似std::map 的Key
struct tagGoodsID {};
struct tagGoodsGroupID {};

// 声明多索引结构，主要绑定索引类型可以与指定成员的一一映射
using MultiIndexFeeIncre =
boost::multi_index::multi_index_container<
	stru_AccountFeeIncre,    // 数据结构，用于索引的对象
	boost::multi_index::indexed_by<    // 创建索引，可以是一个或者多个。分别以',' 分隔
									   // 创建唯一索引，不允许插入该字段的值相同的两个对象到此容器中。
	boost::multi_index::ordered_unique<
	boost::multi_index::tag<tagGoodsID>,    // 索引标签
	BOOST_MULTI_INDEX_MEMBER(stru_AccountFeeIncre, int32_t, nGoodsID)    // 该索引绑定的成员
	>,
	// 创建非唯一索引，允许多个相同的值到此容器中
	boost::multi_index::ordered_non_unique<
	boost::multi_index::tag<tagGoodsGroupID>,
	BOOST_MULTI_INDEX_MEMBER(stru_AccountFeeIncre, int32_t, nGoodsGroupID)
	>
	>
>;

using C_ITER_FEE_INCRE = MultiIndexFeeIncre::const_iterator;
using PAIR_RANGE_FEE_INCRE = std::pair<C_ITER_FEE_INCRE, C_ITER_FEE_INCRE>;
using C_ITER_ID_FEE_INCRE = MultiIndexFeeIncre::index<tagGoodsID>::type::const_iterator;
using C_ITER_GROUP_FEE_INCRE = MultiIndexFeeIncre::index<tagGoodsGroupID>::type::const_iterator;
using PAIR_RANGE_GROUP_FEE_INCRE = std::pair<C_ITER_GROUP_FEE_INCRE, C_ITER_GROUP_FEE_INCRE>;

// 定义多索引容器实例
static MultiIndexFeeIncre s_multiAccountFeeIncre;
// 定义容器的索引实例的引用 - 非const 版本
static MultiIndexFeeIncre::index<tagGoodsID>::type &INDEX_ID_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsID>();
static MultiIndexFeeIncre::index<tagGoodsGroupID>::type &INDEX_GROUP_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsGroupID>();
// 定义容器的索引实例的引用 - const 版本
static const MultiIndexFeeIncre::index<tagGoodsID>::type &C_INDEX_ID_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsID>();
static const MultiIndexFeeIncre::index<tagGoodsGroupID>::type &C_INDEX_GROUP_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsGroupID>();

// template 版本
MultiIndexFeeIncre::template index<tagGoodsID>::type &TPLT_INDEX_ID = s_multiAccountFeeIncre.template get<tagGoodsID>();
MultiIndexFeeIncre::template index<tagGoodsGroupID>::type &TPLT_INDEX_GROUP = s_multiAccountFeeIncre.template get<tagGoodsGroupID>();

TEST(TestBoostUse, MultiIndex)
{
	const int32_t GROUP_ID_01 = 1;
	const int32_t GROUP_ID_02 = 2;
	int64_t nExpectSize = 0;

	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	int64_t nGoodsID = 1;
	stru_AccountFeeIncre stFeeIncre;
	stFeeIncre.nAccountID = 1;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_01;
	stFeeIncre.nFeeMode = 0;
	stFeeIncre.nTradeMode = 1;
	stFeeIncre.dFeeValue = 0.5;

	// 商品组1
	int32_t nExpectSizeGroupID_1 = 0;
	// 插入一条
	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_1;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// 插入与唯一索引相同的值的对象，插入失败
	s_multiAccountFeeIncre.emplace(stFeeIncre);
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// 插入一条
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_01;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_1;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// 插入一条
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_01;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_1;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// 插入到另一个商品组
	int32_t nExpectSizeGroupID_2 = 0;
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_02;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_2;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// 插入一条
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_02;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_2;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// 查询
	do
	{
		// 唯一索引的查询，结果仅有一条记录
		int nTempGoodsID = 1;
		C_ITER_ID_FEE_INCRE c_iter_id = INDEX_ID_FEE_INCRE.find(nTempGoodsID);
		ASSERT_NE(c_iter_id, INDEX_ID_FEE_INCRE.end());

		// 非唯一索引的查询，结果为一组记录
		PAIR_RANGE_GROUP_FEE_INCRE range = TPLT_INDEX_GROUP.equal_range(GROUP_ID_01);
		int nTempSize = 0;
		for (auto it = range.first; it != range.second; ++it)
		{
			EXPECT_EQ(GROUP_ID_01, it->nGoodsGroupID);
			++nTempSize;
		}

		EXPECT_EQ(nExpectSizeGroupID_1, nTempSize);
	} while (false);

	// 修改
	do
	{
		// 拷贝副本
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t nTempGoodsID = 1;

		C_ITER_ID_FEE_INCRE c_iter_id = bak_multiAccountFeeIncre.get<tagGoodsID>().find(nTempGoodsID);
		EXPECT_NE(c_iter_id, bak_multiAccountFeeIncre.get<tagGoodsID>().end());
		if (c_iter_id == bak_multiAccountFeeIncre.get<tagGoodsID>().end())
		{
			break;
		}

		stru_AccountFeeIncre newObj;    // 未设置值使用内存随机值即可
		newObj.nGoodsID = c_iter_id->nGoodsID; // 唯一性主键不修改
		newObj.nGoodsGroupID = nExpectSizeGroupID_2;    // 商品组ID改到2 非唯一性主键修改
		bool bResTemp = bak_multiAccountFeeIncre.replace(c_iter_id, newObj);
		EXPECT_TRUE(bResTemp);
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	do
	{
		// 拷贝副本
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t nTempGoodsID = 1;

		C_ITER_ID_FEE_INCRE c_iter_id = bak_multiAccountFeeIncre.get<tagGoodsID>().find(nTempGoodsID);
		EXPECT_NE(c_iter_id, bak_multiAccountFeeIncre.get<tagGoodsID>().end());
		if (c_iter_id == bak_multiAccountFeeIncre.get<tagGoodsID>().end())
		{
			break;
		}

		stru_AccountFeeIncre newObj;
		newObj.nGoodsID = 23487954;    // 修改唯一性主键
		newObj.nGoodsGroupID = c_iter_id->nGoodsGroupID;    // 非唯一性主键不修改
		bool bResTemp = bak_multiAccountFeeIncre.replace(c_iter_id, newObj);
		EXPECT_TRUE(bResTemp);
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	// 删除
	do
	{
		// 拷贝副本
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t bakExpectSizeGroupID_1 = nExpectSizeGroupID_1;

		// 先删除商品组1 中的一个商品
		int nTempGoodsID = 1;
		C_ITER_ID_FEE_INCRE c_iter_id = bak_multiAccountFeeIncre.get<tagGoodsID>().find(nTempGoodsID);
		ASSERT_NE(c_iter_id, bak_multiAccountFeeIncre.get<tagGoodsID>().end());
		bak_multiAccountFeeIncre.erase(c_iter_id);
		--bakExpectSize;
		--bakExpectSizeGroupID_1;
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());

		// 删除商品组1 的元素
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.get<tagGoodsID>().size());
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.get<tagGoodsGroupID>().size());
		bak_multiAccountFeeIncre.template get<tagGoodsGroupID>().erase(GROUP_ID_01);
		bakExpectSize -= bakExpectSizeGroupID_1;
		bakExpectSizeGroupID_1 = 0;
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	do
	{
		// 拷贝副本
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t bakExpectSizeGroupID_2 = nExpectSizeGroupID_2;

		// 删除商品组2 的元素
		bak_multiAccountFeeIncre.template get<tagGoodsGroupID>().erase(GROUP_ID_02);
		bakExpectSize -= bakExpectSizeGroupID_2;
		bakExpectSizeGroupID_2 = 0;
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	do
	{
		// 拷贝副本
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakGoodsID = nGoodsID;
		int32_t bakExpectSize = nExpectSize;

		// 按唯一性主键: 商品ID 进行删除
		do
		{
			bak_multiAccountFeeIncre.template get<tagGoodsID>().erase(bakGoodsID);
			--bakExpectSize;
			EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
		} while (--bakGoodsID > 0);
	} while (false);
}


int main(int argc, char *argv[])
{
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}