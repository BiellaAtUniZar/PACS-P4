#pragma once

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include "join_threads.hpp"
#include "threadsafe_queue.hpp"

class thread_pool {
	using task_type = void();

	std::atomic<bool> _done;
	threadsafe_queue<std::function<task_type>> _queue;
	std::vector<std::thread> _pool;
	join_threads _joiner;

	void worker_thread() {
		while (!_done) {
			std::function<task_type> task;
			if (_queue.try_pop(task)) {
				task();
			} else {
				std::this_thread::yield();
			}
		}
	}

public:
	/**
	 * Constructor
	 * @params num_threads the number of working threads to put in the pool
	 */
	thread_pool(size_t num_threads = std::thread::hardware_concurrency()) :
		_done(false), _pool(num_threads), _joiner(_pool) {

		for (size_t i = 0; i < num_threads; i++) {
			_pool.push_back(std::thread(&thread_pool::worker_thread));
		}
	}

	/**
	 * Destructor
	 */
	~thread_pool() { wait(); }

	/**
	 *Blocking call untill the queue isn't done doing the job
	 */
	void wait() {
		// Active wait
		std::this_thread::sleep_for(std::chrono::seconds(2));
		if (_done)
			return;
	}


	template<typename F>
	void submit(F f) {
		_queue.push(std::function<task_type>(f));
	}
};
