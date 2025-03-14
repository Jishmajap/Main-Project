<template>
  <navigation />
  <section class="flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen lg:py-0 bg-gray-200 w-full">
    <div class="flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen lg:py-0 bg-gray-200 w-full">
      <div class="max-w-sm w-full bg-[#f8f4f3] rounded-lg shadow-sm :bg-gray-800 p-4 md:p-6">
        <div class="flex justify-between mb-5">
          <div class="grid gap-4 grid-cols-2">
            <div>
              <h5 class="inline-flex items-center text-gray-500 :text-gray-400 leading-none font-normal mb-2">Active Users</h5>
              <p class="text-gray-900 :text-white text-2xl leading-none font-bold">{{ activeUsersCount }}</p>
            </div>
            <div>
              <h5 class="inline-flex items-center text-gray-500 :text-gray-400 leading-none font-normal mb-2">Inactive Users</h5>
              <p class="text-gray-900 :text-white text-2xl leading-none font-bold">{{ inactiveUsersCount }}</p>
            </div>
          </div>
        </div>
      </div>
      <div class="chart-container">
        <TagTapChart :tags="tags" />
      </div>
    </div>
  </section>
</template>

<script>
import navigation from '../components/navigation.vue'
import TagTapChart from '../components/TagTapChart.vue'
import { collection, getDocs, getFirestore } from "firebase/firestore";
import router from '../router';
import isLogin from '../utils/userValidation';

export default {
  name: 'analytics',
  components: {
    navigation,
    TagTapChart
  },
  data() {
    return {
      activeUsersCount: 0,
      inactiveUsersCount: 0,
      tags: []
    };
  },
  methods: {
    async fetchUserCounts() {
      try {
        const db = getFirestore();
        const querySnapshot = await getDocs(collection(db, "student"));

        let activeUsers = 0;
        let inactiveUsers = 0;
        querySnapshot.forEach((doc) => {
          const studentData = doc.data();
          if (studentData.balance && studentData.balance > 0) {
            activeUsers++;
          } else {
            inactiveUsers++;
          }
        });
        this.activeUsersCount = activeUsers;
        this.inactiveUsersCount = inactiveUsers;
      } catch (error) {
        console.error("Error fetching user counts:", error);
      }
    },
    async fetchTagTaps() {
      try {
        const db = getFirestore();
        const querySnapshot = await getDocs(collection(db, "activities"));
        const tagsData = [];

        querySnapshot.forEach((doc) => {
          const activityData = doc.data();
          tagsData.push({
            name: activityData.name,
            tagid: activityData.tagid,
            tapCount: activityData.tapCount
          });
        });

        this.tags = tagsData;
      } catch (error) {
        console.error("Error fetching tag taps:", error);
      }
    }
  },
  beforeMount() {
    if (!isLogin()) {
      router.push('/stud_login');
    }
  },
  mounted() {
    this.fetchUserCounts();
    this.fetchTagTaps();
  }
};
</script>

<style scoped>
.chart-container {
  position: relative;
  height: 400px;
  width: 100%;
}
</style>