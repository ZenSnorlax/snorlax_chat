
use std::cmp::Ordering;

#[derive(PartialEq, Eq, Clone, Copy, Debug)]
struct Job {
    a: usize,
    b: usize,
}

impl Ord for Job {
    fn cmp(&self, other: &Self) -> Ordering {
        // 如果a小于其他作业的b，则应该排在前面
        if self.a < other.b {
            return Ordering::Less;
        }
        // 如果a大于其他作业的b，则应该排在后面
        if self.a > other.b {
            return Ordering::Greater;
        }
        // 如果a等于其他作业的b，那么比较b的值，较小的作业应该排在前面
        self.b.cmp(&other.b)
    }
}

impl PartialOrd for Job {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn main() {
    // 示例作业数据
    let mut jobs = vec![
        Job { a: 2, b: 4 },
        Job { a: 5, b: 3 },
        Job { a: 1, b: 6 },
        Job { a: 8, b: 2 },
        Job { a: 6, b: 5 },
    ];

    // 对作业进行排序
    jobs.sort();

    // 打印排序后的作业
    for job in &jobs {
        println!("Job a: {}, b: {}", job.a, job.b);
    }
}}