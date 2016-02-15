#pragma once

/// <summary>
/// This class cannot be copied, therefore all children of this class will also
/// not be copyable. This class uses C++11 "= delete" syntax to disable all
/// of these operations.
/// </summary>
class NonCopyable {
protected:
	/// Allow the default constructor
	NonCopyable() noexcept = default;
	/// Allow the default destructor
	~NonCopyable() noexcept = default;
private:
	/// Disable the copy constructor
	NonCopyable(const NonCopyable&) noexcept = delete;
	/// Disable the move constructor
	NonCopyable(NonCopyable&&) noexcept = delete;

	/// Disable the assignment operator
	NonCopyable& operator=(const NonCopyable&) noexcept = delete;
	/// Disable the move-assign operator
	NonCopyable& operator=(NonCopyable&&) noexcept = delete;
};