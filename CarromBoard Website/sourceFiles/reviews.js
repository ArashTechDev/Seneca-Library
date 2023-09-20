window.onload = function() {
    populateReviews();

    const form = document.getElementById('new-review-form');
    form.addEventListener('submit', function(event) {
        event.preventDefault();

        const newReview = {
            name: document.getElementById('name').value,
            date: document.getElementById('date').value,
            rating: parseInt(document.getElementById('rating').value),
            review: document.getElementById('review').value
        };

        window.reviewData.push(newReview);

        addReviewToDOM(newReview);

        // Clear the form
        form.reset();
    });
};

function populateReviews() {
    for (let review of window.reviewData) {
        addReviewToDOM(review);
    }
}

function addReviewToDOM(review) {
    const reviewElement = document.createElement('div');
    reviewElement.className = 'review-item';
    reviewElement.innerHTML = `
        <strong>${review.name}</strong> on <span>${review.date}</span> rated it <span>${'*'.repeat(review.rating)}</span><br>
        <p>${review.review}</p>
    `;

    document.getElementById('reviews').appendChild(reviewElement);
}
